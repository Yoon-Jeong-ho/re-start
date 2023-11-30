package hello.servlet.domain.member;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MemberRepository {
    private static Map<Long, Member> store = new HashMap<>();
    private static Long sequence = 0L;

    private static final  MemberRepository instance = new MemberRepository();
    public static MemberRepository getInstance(){ // 무조건 이걸로 조회해야한다.
        return instance;
    }

    private MemberRepository(){ // 아무나 생성하지 못하도록 생성자 막기

    }

    public Member save(Member member){
        member.setId(++sequence);
        store.put(member.getId(), member);
        return member;
    }

    public Member findById(Long id){
        return store.get(id);
    }

    public List<Member> findAll(){
        return new ArrayList<>(store.values());
    }

    public void clearStore(){ // 테스트에서 사용할 코드
        store.clear();
    }
}
