using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems; //UI�� ������ ������ �׳� ������ ������ Ȯ��


public class PlayerCtrl : MonoBehaviour
{
    public GameObject joyStick, mainView, playView;
    public Button btn;
    Animator anim;
    GameObject coll;
    public Sprite use, kill;

    public Text text_Cool;


    public float speed;
    public Settings settings_script;

    public bool isCantMove,isMission; // �̰� settings���� �ٲ۴�.

    float timer;
    bool isCool, isAnim;
    KillCtrl killCtrl_script;

    private void Start()
    {
        anim = GetComponent<Animator>();
        Camera.main.transform.parent = transform; //ĳ���� ��Ż ����
        Camera.main.transform.localPosition = new Vector3(0, 0, -10);

        if (isMission)
        {// �̼�
            btn.GetComponent<Image>().sprite = use;
            text_Cool.text = "";
        }
        else
        {// ų����Ʈ
            killCtrl_script = FindObjectOfType<KillCtrl>();

            btn.GetComponent<Image>().sprite = kill;

            timer = 5;
            isCool = true;
        }
    }
    private void Update()
    {
        // ��Ÿ��
        if (isCool)
        {
            timer -= Time.deltaTime; // 1�ʿ� 1�� �����Ѵ�.
            text_Cool.text = Mathf.Ceil(timer).ToString();
            if(text_Cool.text == "0")
            {
                text_Cool.text = "";
                isCool = false;

            }
        }
        if (isCantMove)
        {
            joyStick.SetActive(false);// �������̴� ��Ȳ������ ���̽�ƽ�� ������ �ʴ´�.
        }
        else
        {
            Move();
        }

        //�ִϸ��̼��� �����߰�, �����ٸ�
        if (isAnim && killCtrl_script.kill_anim.GetComponent<Animator>().GetCurrentAnimatorStateInfo(0).normalizedTime >= 1)
        {
            isAnim = false;
            killCtrl_script.kill_anim.SetActive(false);
            isCantMove = false;
            killCtrl_script.Kill();
        }
    }
    
    // ĳ���� ������ ����
    void Move()
    {
        if (settings_script.isJoyStick)
        {
            joyStick.SetActive(true);
        }
        else
        {
            joyStick.SetActive(false);

            // �����¿츦 ��ġ�Ͽ� �����̱�

            //Ŭ���ߴ��� �Ǵ�.
            if (Input.GetMouseButton(0))
            {            // ��Ŭ�� ������ �ִ� �� ��ǻ�� ����� �� ���ش�.
#if UNITY_EDITOR
                if (!EventSystem.current.IsPointerOverGameObject())
                {//Ŭ���� ���� UI�� �ƴ϶��
                    Vector3 dir = (Input.mousePosition - new Vector3(Screen.width * 0.5f, Screen.height * 0.5f)).normalized; // ȭ�� ���߾��� ���� �󸶳� �̵��ϴ����� �븻 ����ȭ �Ѵ�.

                    transform.position += dir * speed * Time.deltaTime;

                    anim.SetBool("isWalk", true);// � �Ұ��� ���


                    //�������� �̵�
                    if (dir.x < 0)
                    {
                        transform.localScale = new Vector3(-1, 1, 1);
                    }
                    else
                    {
                        //���������� �̵�
                        transform.localScale = new Vector3(1, 1, 1);

                    }
                }
#else
#endif
                if (!EventSystem.current.IsPointerOverGameObject(Input.GetTouch(0).fingerId))
                {//Ŭ���� ���� UI�� �ƴ϶��
                    Vector3 dir = (Input.mousePosition - new Vector3(Screen.width * 0.5f, Screen.height * 0.5f)).normalized; // ȭ�� ���߾��� ���� �󸶳� �̵��ϴ����� �븻 ����ȭ �Ѵ�.

                    transform.position += dir * speed * Time.deltaTime;

                    anim.SetBool("isWalk", true);// � �Ұ��� ���


                    //�������� �̵�
                    if (dir.x < 0)
                    {
                        transform.localScale = new Vector3(-1, 1, 1);
                    }
                    else
                    {
                        //���������� �̵�
                        transform.localScale = new Vector3(1, 1, 1);

                    }
                }
                

            }
            else
            { // �̵����� �������
                anim.SetBool("isWalk", false);// � �Ұ��� ���

            }
        }

    }

    // ĳ���� ����
    public void DestroyPlayer()
    {
        Camera.main.transform.parent = null;
        Destroy(gameObject);
    }

    //Ʈ���ſ� ������ ���
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.tag == "Mission" && isMission)
        {
            coll = collision.gameObject;
            btn.interactable = true; 
        }

        if (collision.tag == "NPC" && !isMission && !isCool)
        {// ų�����̴�
            coll = collision.gameObject;
            btn.interactable = true;
        }
    }

    //Ʈ���ſ� ���������
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.tag == "Mission" && isMission)
        {
            coll = null;

            btn.interactable = false;
        }

        if (collision.tag == "NPC" && !isMission)
        {// ų�����̴�
            coll = null;
            btn.interactable = false;
        }
    }

    //��ư ������ ȣ��
    public void ClickButton()
    {
        // �̼��� ��
        if (isMission)
        {
            //�̼� ��ŸƮ�� ȣ��
            // �̼� ��ŸƮ ��ũ��Ʈ�� �޾ƿ;� �ϴµ� �����ϰ� ȣ�� ����
            coll.SendMessage("MissionStart");


        }
        //ų����Ʈ�� �� 
        else
        {
            Kill();
        }


        isCantMove = true;
        btn.interactable = false;


    }
     
    void Kill()
    {
        //���̴� �ִϸ��̼�
        killCtrl_script.kill_anim.SetActive(true); // �ִϸ��̼����� �� ������ �Ѵ�.
        isAnim = true;

        //���� �̹����� ����
        coll.SendMessage("Dead");

        // ���� NPC�� �ٽ� ���� �� ����.
        coll.GetComponent<CircleCollider2D>().enabled = false;

    }
    //�̼� �����ϸ� ȣ��
    // mission1���Ͽ��� ȣ��
    public void MissionEnd()
    {
        isCantMove = false;
    }
}
