// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("질문, "+GetAddress_Form(NPChar)+"?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("음, 이게 다 무슨 짓이야, "+GetAddress_Form(NPChar)+"? ","또 이상한 질문이야? 이봐, 가서 럼주나 한잔 해.")+"","오늘 하루만 해도, 그 질문을 벌써 세 번째 꺼내는군..."+GetSexPhrase(" 이게 애정의 표시인가?","")+"","또 질문이 있나 보군. "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었어","지금은 할 말이 없어."),"아니, 아니, 이쁜이...","말도 안 돼, 자기야...","아니, 무슨 질문이야?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
            {
                link.l1 = "이봐, 여자, 네가 내 옛 동료 프랑수아 곤티에랑 꽤 가까웠다던데. 아주 가까웠다지...";
                link.l1.go = "Jamaica_ratW_1";
            }
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
            {
				if (CheckCharacterItem(pchar, "jewelry43"))
				{
					link.l1 = "보석이 박힌 네 목걸이를 가져왔어. 여기 있다. 앞으로는 너 같은 욕심 많은 여자들한테서 신이 나를 지켜주시길.";
					link.l1.go = "Jamaica_ratW_5";
				}
				else
				{
					link.l1 = "지금은 아무것도 없어. 네 목걸이를 찾고 있어.";
					link.l1.go = "exit";
				}
            }
			
		break;
		
		case "Jamaica_ratW_1":
            dialog.text = "그래, 우리가 그랬어. 그래서 뭐? 난 결혼한 여자도 아니고, 내가 원하는 사람이랑 시간을 보내지. 프랑수아는 아주 점잖은 선원이야, 우리 동네 어부나 농부들이랑은 달라. 그는 정말... 아! 그리고 나한테 멋진 선물도 줬다니까!";
            link.l1 = "좋아, 이제 그만해! 내 동료가 어떤 사람인지 내가 잘 아니까 굳이 네가 하나하나 말할 필요 없어. 너희 둘 사이에 무슨 일이 있었는지 난 관심 없어. 결혼을 하든 말든 상관없어. 난 당장 그를 찾아야 해, 알겠어? 어디로 갔는지 알아?";
            link.l1.go = "Jamaica_ratW_2";
        break;
		
		case "Jamaica_ratW_2":
            dialog.text = "히히... 네가 그 녀석의 동료라면서 어디 갔는지도 모른다고? 그거 참 웃기네!";
            link.l1 = "웃길 거 하나도 없어, 여자. 자메이카에서 만나기로 했고, 그다음엔 같이 항해할 계획이 있었거든... 무슨 말인지 알겠지. 나 혼자선 그걸 할 수 없고, 걔는 어디로 갔는지 알 수가 없잖아!";
            link.l1.go = "Jamaica_ratW_3";
        break;
		
		case "Jamaica_ratW_3":
            dialog.text = "알겠소. 뭐, 그렇게 이득이 큰 항해가 곧 있을 거라면, 그리고 자네와 프랑수아가 친구 사이라면... 그가 어디로 떠났는지 알려주겠소, 하지만 약간의 보상이 필요하네.";
            link.l1 = "그래, 사정은 잘 알지. 얼마를 원하는 거야?";
            link.l1.go = "Jamaica_ratW_4";
        break;
		
		case "Jamaica_ratW_4":
            dialog.text = "오, 정말 속물 같군! 돈 따위는 필요 없어. 아니, 난 특별한 걸 원하지. 프랑수아가 보석이 박힌 멋진 목걸이를 주겠다고 약속했거든. 이미 친구들에게 자랑도 했는데 그 녀석은 바로 사라져 버렸지... 펜던트를 가져오면 그가 어디로 갔는지 알려줄게, 히히!";
            link.l1 = "이 건방진 계집 같으니! 네덜란드 계집애들은 정말 욕심도 끝이 없구나! 좋아, 목걸이 가져가.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_5");
			pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
        break;
		
		case "Jamaica_ratW_5":
            dialog.text = "아, 정말 아름답군! 이제 내 친구들이 질투로 초록이 되겠어!";
            link.l1 = "그들에게 내 애도를 전해라. 이제 말해 봐라. 프랑수아는 어디로 갔지?";
            link.l1.go = "Jamaica_ratW_6";
			RemoveItems(PChar, "jewelry43", 1);
        break;
		
		case "Jamaica_ratW_6":
            dialog.text = "네, 물론입니다, 나리. 프랑수아는 쿠바의 아바나로 항해해 떠났습니다.";
            link.l1 = "값비싼 정보 고맙다, 계집아. 그게 내가 원한 전부야.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_6");
			pchar.questTemp.Slavetrader = "FindRatHavana";
        break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
