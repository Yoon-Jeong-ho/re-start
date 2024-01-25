using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class Mission6 : MonoBehaviour
{
    public bool[] isColor= new bool[4];
    public RectTransform[] rights;
    public LineRenderer[] lines;

    Animator anim;
    PlayerCtrl playerCtrl_script;
    MissionCtrl missionCtrl_script;

    Vector2 clickPos;
    LineRenderer line;
    float leftY, rightY;
    bool isDrag;

    Color leftC, rightC;

    // Start is called before the first frame update
    void Start()
    {
        //getcomponent를 그냥 쓰면 안된다. 여기서 애니메이션은 하위 파일에 있다.
        anim = GetComponentInChildren<Animator>();

        missionCtrl_script = FindObjectOfType<MissionCtrl>();

    }

    private void Update()
    {
        if (isDrag)
        {
            line.SetPosition(1,new Vector3((Input.mousePosition.x- clickPos.x)* 1920f /Screen.width, (Input.mousePosition.y - clickPos.y) * 1080f /Screen.height,-10));


            // 드래그 끝
            if (Input.GetMouseButtonUp(0))
            { // 움직임이 끝났을 때 위치를 원위치해준다.
                Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);// 마우스 위치에 레이저

                RaycastHit hit;
                //오른쪽 선에 닿았다면

                if (Physics.Raycast(ray, out hit))
                {// 레이케스트를 쏴서 맞은 것이 있다.

                    GameObject rightLine = hit.transform.gameObject;
                    rightY = rightLine.GetComponent<RectTransform>().anchoredPosition.y;     //오른쪽 선 y값

                    //오른쪽 선 색상
                    rightC = rightLine.GetComponent<Image>().color;


                    //이어주기
                    line.SetPosition(1, new Vector3(500,rightY-leftY , -10));

                    // 색 비교
                    if(leftC == rightC)
                    {
                        switch (leftY)
                        {
                            case 225: isColor[0] = true; break; 
                            case 75: isColor[1] = true; break; 
                            case -75: isColor[2] = true; break; 
                            case -225: isColor[3] = true; break; 
                        }
                    }
                    else
                    {
                        switch (leftY)
                        {
                            case 225: isColor[0] = false; break;
                            case 75: isColor[1] = false; break;
                            case -75: isColor[2] = false; break;
                            case -225: isColor[3] = false; break;
                        }

                    }

                    // 성공 여부 체크
                    if(isColor[0] && isColor[1] && isColor[2] && isColor[3])    
                    {
                        Invoke("MissionSuccess", 0.2f);
                    }
                }
                else
                {
                    // 닿지 않았다면

                    line.SetPosition(1, new Vector3(0, 0, -10));

                }



                isDrag = false;
            }

        }
    }

    //미션 시작
    public void MissionStart()
    {
        anim.SetBool("IsUp", true);
        playerCtrl_script = FindObjectOfType<PlayerCtrl>();
        //초기화
        for (int i = 0; i <4; i++)
        {
            isColor[i] = false;

            lines[i].SetPosition(1, new Vector3(0,0,-10));
        }


            // 오른쪽 랜덤 작업
            for (int i = 0; i < rights.Length; i++)
        {
            Vector3 temp = rights[i].anchoredPosition;

            int rand = Random.Range(0, 4);
            rights[i].anchoredPosition = rights[rand].anchoredPosition;

            rights[rand].anchoredPosition= temp;
        }
    }

    //x버튼 누르면 호출
    public void ClickCancle()
    {
        anim.SetBool("IsUp", false);
        playerCtrl_script.MissionEnd();
    }

    //선 누르면 호출
    public void ClickLine(LineRenderer click)
    {
        clickPos = Input.mousePosition;
        line = click;

        leftY = click.transform.parent.GetComponent<RectTransform>().anchoredPosition.y;//왼쪽 선 y값

        isDrag = true;

        //왼쪽 선 색상
        leftC = click.transform.parent.GetComponent<Image>().color;
    }


    // 미션 성공하면 호출될 함수
    public void MissionSuccess()
    {
        ClickCancle();
        missionCtrl_script.MissionSuccess(GetComponent<CircleCollider2D>());

    }
}
