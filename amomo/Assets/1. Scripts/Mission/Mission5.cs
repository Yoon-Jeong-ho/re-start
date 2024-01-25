using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class Mission5 : MonoBehaviour
{
    public Transform rotate,handle; 
    Animator anim;
    PlayerCtrl playerCtrl_script;

    public Color blue, red;
    RectTransform rect_handle;
    MissionCtrl missionCtrl_script;

    bool isDrag,isPlay;
    float rand;
    // Start is called before the first frame update
    void Start()
    {
        //getcomponent�� �׳� ���� �ȵȴ�. ���⼭ �ִϸ��̼��� ���� ���Ͽ� �ִ�.
        anim = GetComponentInChildren<Animator>();
        rect_handle = handle.GetComponent<RectTransform>();

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
                rect_handle.anchoredPosition = new Vector2(184, Mathf.Clamp(rect_handle.anchoredPosition.y, -195, 195)); // ��������!


                // �巡�� ��
                if (Input.GetMouseButtonUp(0))
                { // �������� ������ �� �ڵ��� ��ġ�� ����ġ���ش�.
                    
                    // ���� ���� üũ
                    if(rect_handle.anchoredPosition.y>-5 && rect_handle.anchoredPosition.y < 5)
                    {
                        Invoke("MissionSuccess", 0.2f);
                        isPlay = true;
                    }
                    

                    isDrag = false;
                }

            }

            rotate.eulerAngles = new Vector3(0, 0, 90 * rect_handle.anchoredPosition.y / 195);// �ִ밪 �������� �ڽ��Ѵ�.

            // ���信 ����� ���� �� ����
            if (rect_handle.anchoredPosition.y > -5 && rect_handle.anchoredPosition.y < 5)
            {
                rotate.GetComponent<Image>().color = blue;
            }
            else
            {
                rotate.GetComponent<Image>().color = red;

            }
        }
    }

    //�̼� ����
    public void MissionStart()
    {
        anim.SetBool("IsUp", true);
        playerCtrl_script = FindObjectOfType<PlayerCtrl>();
        // �ʱ�ȭ
        rand = 0;


        // ���� �ڵ� ��ġ
        rand = Random.Range(-195, 195); // 0�� ���� �� �����Ƿ� -10 ~ 10�� ����ó�� ���ش�.
        while(rand >-10 && rand < 10)
        {
            rand = Random.Range(-195, 195);
        }
        rect_handle.anchoredPosition = new Vector2(184, rand);
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
        missionCtrl_script.MissionSuccess(GetComponent<CircleCollider2D>());

        ClickCancle();
    }
}
