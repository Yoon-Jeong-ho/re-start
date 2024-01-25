using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// 1. ��ƽ �巡�� + ���� �� (��ƽ�� �̺�Ʈ Ʈ���Ÿ� �������� �Ѵ�.)
// 2. �巡���� ��ŭ ĳ���͸� �̵�

public class JoyStick : MonoBehaviour
{
    public RectTransform stick, backGround; // ū���� �������� �޾ƿ´�.
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
        // �巡�� �ϴ� ����
        if (isDrag)
        {// ��ƽ�� ��ġ�� ���콺�� ��������.
            //stick.position = Input.mousePosition;
            Vector2 vec = Input.mousePosition - backGround.position; // ū ���׶�� �������� ����Ѵ�.
            stick.localPosition = Vector2.ClampMagnitude(vec, limit);

            Vector3 dir = (stick.position - backGround.position).normalized;
            transform.position += dir * playerCtrl_script.speed * Time.deltaTime;

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
            // �巡�� ������
            if (Input.GetMouseButtonUp(0))
            {// ��ġ�� ������ ��
                stick.localPosition = new Vector3(0, 0, 0);
                //���� �������� �θ�(���̽�ƽ)���� ������ ��ġ

                isDrag = false;
            }
        }
        else
        {
            anim.SetBool("isWalk", false);// � �Ұ��� ���

        }
    }
    //��ƽ�� ������ ȣ�� �� �Լ�
    public void ClickStick()
    {
        isDrag = true;
    }

}
