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
        //getcomponent를 그냥 쓰면 안된다. 여기서 애니메이션은 하위 파일에 있다.
        anim = GetComponentInChildren<Animator>();
        rect_handle = handle.GetComponent<RectTransform>();

        missionCtrl_script = FindObjectOfType<MissionCtrl>();

    }

    private void Update()
    {
        if (isPlay)
        {
            // 드래그
            if (isDrag)
            { // 핸들의 위치를 이동해준다.
                handle.position = Input.mousePosition;
                rect_handle.anchoredPosition = new Vector2(184, Mathf.Clamp(rect_handle.anchoredPosition.y, -195, 195)); // 제한해줌!


                // 드래그 끝
                if (Input.GetMouseButtonUp(0))
                { // 움직임이 끝났을 때 핸들의 위치를 원위치해준다.
                    
                    // 성공 여부 체크
                    if(rect_handle.anchoredPosition.y>-5 && rect_handle.anchoredPosition.y < 5)
                    {
                        Invoke("MissionSuccess", 0.2f);
                        isPlay = true;
                    }
                    

                    isDrag = false;
                }

            }

            rotate.eulerAngles = new Vector3(0, 0, 90 * rect_handle.anchoredPosition.y / 195);// 최대값 기준으로 박싱한다.

            // 정답에 가까워 지면 색 변경
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

    //미션 시작
    public void MissionStart()
    {
        anim.SetBool("IsUp", true);
        playerCtrl_script = FindObjectOfType<PlayerCtrl>();
        // 초기화
        rand = 0;


        // 랜덤 핸들 위치
        rand = Random.Range(-195, 195); // 0이 나올 수 있으므로 -10 ~ 10은 예외처리 해준다.
        while(rand >-10 && rand < 10)
        {
            rand = Random.Range(-195, 195);
        }
        rect_handle.anchoredPosition = new Vector2(184, rand);
        isPlay = true;
    }

    //x버튼 누르면 호출
    public void ClickCancle()
    {
        anim.SetBool("IsUp", false);
        playerCtrl_script.MissionEnd();
    }

    //손잡이 누르면 호출
    public void ClickHandle()
    {
        isDrag = true;
    }


    // 미션 성공하면 호출될 함수
    public void MissionSuccess()
    {
        missionCtrl_script.MissionSuccess(GetComponent<CircleCollider2D>());

        ClickCancle();
    }
}
