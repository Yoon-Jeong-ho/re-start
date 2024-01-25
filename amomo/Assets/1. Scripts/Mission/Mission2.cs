using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class Mission2 : MonoBehaviour
{
    public Transform trash,handle; 
    Animator anim;
    PlayerCtrl playerCtrl_script;
    public GameObject bottom; //�ٴ��� ���� �Ѵ�.
    public Animator anim_shake;


    RectTransform rect_handle;

    bool isDrag,isPlay;
    Vector2 originPos;
    MissionCtrl missionCtrl_script;

    // Start is called before the first frame update
    void Start()
    {
        //getcomponent�� �׳� ���� �ȵȴ�. ���⼭ �ִϸ��̼��� ���� ���Ͽ� �ִ�.
        anim = GetComponentInChildren<Animator>();
        rect_handle = handle.GetComponent<RectTransform>();
        originPos = rect_handle.anchoredPosition;//�ڵ��� �� ��ġ�� ����

        missionCtrl_script = FindObjectOfType<MissionCtrl>();

    }

    private void Update()
    {
        if (isPlay)
        {
            // �巡��
            if (isDrag)
            { // �ڵ��� ��ġ�� �̵����ش�.
                handle.position = Input.mousePosition;
                rect_handle.anchoredPosition = new Vector2(originPos.x, Mathf.Clamp(rect_handle.anchoredPosition.y, -135, -47)); // ��������!

                anim_shake.enabled = true;

                // �巡�� ��
                if (Input.GetMouseButtonUp(0))
                { // �������� ������ �� �ڵ��� ��ġ�� ����ġ���ش�.
                    rect_handle.anchoredPosition = originPos;
                    isDrag = false;
                    anim_shake.enabled = false;

                }

            }

            // ������ ������ ����
            if (rect_handle.anchoredPosition.y <= -130)
            {
                bottom.SetActive(false);
            }
            else
            {
                bottom.SetActive(true);
            }

            // �����Ⱑ ������ �������� �ʰ� �������ش�.
            for (int i = 0; i < trash.childCount; i++)
            {
                if (trash.GetChild(i).GetComponent<RectTransform>().anchoredPosition.y <= -600)
                {
                    Destroy(trash.GetChild(i).gameObject);
                }
            }

            //�������� üũ
            if (trash.childCount == 0)
            {
                MissionSuccess();
                isPlay = false;

                rect_handle.anchoredPosition = originPos;
                isDrag = false;
                anim_shake.enabled = false;
            }
        }
    }

    //�̼� ����
    public void MissionStart()
    {
        anim.SetBool("IsUp", true);
        playerCtrl_script = FindObjectOfType<PlayerCtrl>();
        // �ʱ�ȭ
        for(int i = 0; i < trash.childCount; i++)
        { // ������ ������ ��ŭ
            Destroy(trash.GetChild(i).gameObject);
        }

        // ������ ����
        for(int i = 0; i < 10; i++)
        {   
            // ���
            GameObject trash4 =Instantiate(Resources.Load("Trash/Trash 4"),trash)as GameObject;
            trash4.GetComponent<RectTransform>().anchoredPosition = new Vector2(Random.Range(-180, 180), Random.Range(-180, 180)); // ��ġ ���� ����
            trash4.GetComponent<RectTransform>().eulerAngles = new Vector3(0,0, Random.Range(0, 180)); // ���� ���� ����

            // ĵ
            GameObject trash5 = Instantiate(Resources.Load("Trash/Trash 5"), trash) as GameObject;
            trash5.GetComponent<RectTransform>().anchoredPosition = new Vector2(Random.Range(-180, 180), Random.Range(-180, 180)); // ��ġ ���� ����
            trash5.GetComponent<RectTransform>().eulerAngles = new Vector3(0, 0, Random.Range(0, 180)); // ���� ���� ����

        }        
        for(int i = 0; i < 3; i++)
        {   
            // ��
            GameObject trash1 =Instantiate(Resources.Load("Trash/Trash 1"),trash)as GameObject;
            trash1.GetComponent<RectTransform>().anchoredPosition = new Vector2(Random.Range(-180, 180), Random.Range(-180, 180)); // ��ġ ���� ����
            trash1.GetComponent<RectTransform>().eulerAngles = new Vector3(0,0, Random.Range(0, 180)); // ���� ���� ����

            // ����
            GameObject trash2 = Instantiate(Resources.Load("Trash/Trash 2"), trash) as GameObject;
            trash2.GetComponent<RectTransform>().anchoredPosition = new Vector2(Random.Range(-180, 180), Random.Range(-180, 180)); // ��ġ ���� ����
            trash2.GetComponent<RectTransform>().eulerAngles = new Vector3(0, 0, Random.Range(0, 180)); // ���� ���� ����
            //���
            GameObject trash3 = Instantiate(Resources.Load("Trash/Trash 3"), trash) as GameObject;
            trash3.GetComponent<RectTransform>().anchoredPosition = new Vector2(Random.Range(-180, 180), Random.Range(-180, 180)); // ��ġ ���� ����
            trash3.GetComponent<RectTransform>().eulerAngles = new Vector3(0, 0, Random.Range(0, 180)); // ���� ���� ����

        }
        isPlay = true;
    }

    //x��ư ������ ȣ��
    public void ClickCancle()
    {
        anim.SetBool("IsUp", false);
        playerCtrl_script.MissionEnd();
    }

    //������ ������ ȣ��
    public void ClickHandle()
    {
        isDrag = true;
    }


    // �̼� �����ϸ� ȣ��� �Լ�
    public void MissionSuccess()
    {
        ClickCancle();
        missionCtrl_script.MissionSuccess(GetComponent<CircleCollider2D>());

    }
}
