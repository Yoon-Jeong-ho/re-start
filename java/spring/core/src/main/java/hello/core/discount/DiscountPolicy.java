package hello.core.discount;

import hello.core.member.Member;

public interface DiscountPolicy {

    int discount(Member member,int price); // 리턴이 할인 대상 금액

}
