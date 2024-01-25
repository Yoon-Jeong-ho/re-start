using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems; //UI를 선택한 것인지 그냥 움직인 것인지 확인


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

    public bool isCantMove,isMission; // 이건 settings에서 바꾼다.

    float timer;
    bool isCool, isAnim;
    KillCtrl killCtrl_script;

    private void Start()
    {
        anim = GetComponent<Animator>();
        Camera.main.transform.parent = transform; //캐릭터 이탈 방지
        Camera.main.transform.localPosition = new Vector3(0, 0, -10);

        if (isMission)
        {// 미션
            btn.GetComponent<Image>().sprite = use;
            text_Cool.text = "";
        }
        else
        {// 킬퀘스트
            killCtrl_script = FindObjectOfType<KillCtrl>();

            btn.GetComponent<Image>().sprite = kill;

            timer = 5;
            isCool = true;
        }
    }
    private void Update()
    {
        // 쿨타임
        if (isCool)
        {
            timer -= Time.deltaTime; // 1초에 1씩 감소한다.
            text_Cool.text = Mathf.Ceil(timer).ToString();
            if(text_Cool.text == "0")
            {
                text_Cool.text = "";
                isCool = false;

            }
        }
        if (isCantMove)
        {
            joyStick.SetActive(false);// 못움직이는 상황에서는 조이스틱도 보이지 않는다.
        }
        else
        {
            Move();
        }

        //애니메이션이 시작했고, 끝났다면
        if (isAnim && killCtrl_script.kill_anim.GetComponent<Animator>().GetCurrentAnimatorStateInfo(0).normalizedTime >= 1)
        {
            isAnim = false;
            killCtrl_script.kill_anim.SetActive(false);
            isCantMove = false;
            killCtrl_script.Kill();
        }
    }
    
    // 캐릭터 움직임 관리
    void Move()
    {
        if (settings_script.isJoyStick)
        {
            joyStick.SetActive(true);
        }
        else
        {
            joyStick.SetActive(false);

            // 상하좌우를 터치하여 움직이기

            //클릭했는지 판단.
            if (Input.GetMouseButton(0))
            {            // 좌클릭 누르고 있는 중 컴퓨터 모바일 다 해준다.
#if UNITY_EDITOR
                if (!EventSystem.current.IsPointerOverGameObject())
                {//클릭한 것이 UI가 아니라면
                    Vector3 dir = (Input.mousePosition - new Vector3(Screen.width * 0.5f, Screen.height * 0.5f)).normalized; // 화면 정중앙을 빼서 얼마나 이동하는지를 노말 백터화 한다.

                    transform.position += dir * speed * Time.deltaTime;

                    anim.SetBool("isWalk", true);// 어떤 불값을 어떻게


                    //왼쪽으로 이동
                    if (dir.x < 0)
                    {
                        transform.localScale = new Vector3(-1, 1, 1);
                    }
                    else
                    {
                        //오른쪽으로 이동
                        transform.localScale = new Vector3(1, 1, 1);

                    }
                }
#else
#endif
                if (!EventSystem.current.IsPointerOverGameObject(Input.GetTouch(0).fingerId))
                {//클릭한 것이 UI가 아니라면
                    Vector3 dir = (Input.mousePosition - new Vector3(Screen.width * 0.5f, Screen.height * 0.5f)).normalized; // 화면 정중앙을 빼서 얼마나 이동하는지를 노말 백터화 한다.

                    transform.position += dir * speed * Time.deltaTime;

                    anim.SetBool("isWalk", true);// 어떤 불값을 어떻게


                    //왼쪽으로 이동
                    if (dir.x < 0)
                    {
                        transform.localScale = new Vector3(-1, 1, 1);
                    }
                    else
                    {
                        //오른쪽으로 이동
                        transform.localScale = new Vector3(1, 1, 1);

                    }
                }
                

            }
            else
            { // 이동하지 않을경우
                anim.SetBool("isWalk", false);// 어떤 불값을 어떻게

            }
        }

    }

    // 캐릭터 삭제
    public void DestroyPlayer()
    {
        Camera.main.transform.parent = null;
        Destroy(gameObject);
    }

    //트리거와 접촉한 경우
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.tag == "Mission" && isMission)
        {
            coll = collision.gameObject;
            btn.interactable = true; 
        }

        if (collision.tag == "NPC" && !isMission && !isCool)
        {// 킬게임이다
            coll = collision.gameObject;
            btn.interactable = true;
        }
    }

    //트리거와 떨어진경우
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.tag == "Mission" && isMission)
        {
            coll = null;

            btn.interactable = false;
        }

        if (collision.tag == "NPC" && !isMission)
        {// 킬게임이다
            coll = null;
            btn.interactable = false;
        }
    }

    //버튼 누르면 호출
    public void ClickButton()
    {
        // 미션일 때
        if (isMission)
        {
            //미션 스타트를 호출
            // 미션 스타트 스크립트를 받아와야 하는데 간단하게 호출 가능
            coll.SendMessage("MissionStart");


        }
        //킬퀘스트일 때 
        else
        {
            Kill();
        }


        isCantMove = true;
        btn.interactable = false;


    }
     
    void Kill()
    {
        //죽이는 애니메이션
        killCtrl_script.kill_anim.SetActive(true); // 애니메이션진행 후 끝내야 한다.
        isAnim = true;

        //죽은 이미지로 변경
        coll.SendMessage("Dead");

        // 죽은 NPC는 다시 죽일 수 없다.
        coll.GetComponent<CircleCollider2D>().enabled = false;

    }
    //미션 종료하면 호출
    // mission1파일에서 호출
    public void MissionEnd()
    {
        isCantMove = false;
    }
}
