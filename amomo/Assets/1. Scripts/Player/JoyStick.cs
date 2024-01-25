using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// 1. 스틱 드래그 + 제한 값 (스틱에 이벤트 트리거를 만들어줘야 한다.)
// 2. 드래그한 만큼 캐릭터를 이동

public class JoyStick : MonoBehaviour
{
    public RectTransform stick, backGround; // 큰원의 반지름을 받아온다.
    PlayerCtrl playerCtrl_script;
    bool isDrag;
    float limit;
    Animator anim;


    public void Start()
    {
        anim = GetComponent<Animator>();

        playerCtrl_script = GetComponent<PlayerCtrl>();
        limit = backGround.rect.width * 0.5f;
    }
    public void Update()
    {
        // 드래그 하는 동안
        if (isDrag)
        {// 스틱의 위치를 마우스로 가져간다.
            //stick.position = Input.mousePosition;
            Vector2 vec = Input.mousePosition - backGround.position; // 큰 동그라미 기준으로 계산한다.
            stick.localPosition = Vector2.ClampMagnitude(vec, limit);

            Vector3 dir = (stick.position - backGround.position).normalized;
            transform.position += dir * playerCtrl_script.speed * Time.deltaTime;

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
            // 드래그 끝나면
            if (Input.GetMouseButtonUp(0))
            {// 터치가 끝났을 때
                stick.localPosition = new Vector3(0, 0, 0);
                //로컬 포지션은 부모(조이스틱)으로 부터의 위치

                isDrag = false;
            }
        }
        else
        {
            anim.SetBool("isWalk", false);// 어떤 불값을 어떻게

        }
    }
    //스틱을 누르면 호출 될 함수
    public void ClickStick()
    {
        isDrag = true;
    }

}
