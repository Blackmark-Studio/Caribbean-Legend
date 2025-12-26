// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("뭘 원하지?","무엇을 알고 싶으신가?"),"무슨 일이야, "+GetAddress_Form(NPChar)+"?","그거 세 번째로 나한테 물어보는 거야...","너 정말 지긋지긋하다, 꺼져!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("미안하지만, 마음이 바뀌었어.","별일 아니오, 미안하오."),"잊었네, 미안하군...","세 번째면 성공이겠지, 응? 실례하네...","미안, 미안! 그럼 내가 알아서 나갈게...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "이봐, 미겔 디초소가 지휘하던 프리깃이 1654년 4월에 이 근처에 있었는데, 그때 사라졌어. 그의 배에 대해 더 아는 게 있나? 혹시 무슨 일이 있었는지, 어디로 갔는지 본 적 있나? 기억나는 거라도 있나?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "오호... 그래, 나리, 그건 정말 볼만했지! 그런 건 잊을 수가 없어, 하!";
			link.l1 = "무슨 일이 있었는지 말해줄 수 있나?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "디초소 나리의 프리깃함이 산호세 항구에 닻을 내렸지. 나는 모든 걸 잘 볼 수 있었어, 그래. 정말 훌륭한 프리깃함이었어, 걸작이었지, 내 피 흐르는 심장에 맹세할 수 있어! 선원들은 그 배의 속도를 자랑했는데, 무려 열여섯 노트까지 낼 수 있다더군! 그들은 여기서 하루를 보내고 곧장 토바고 섬으로 출항했어. 그런데 믿기 힘들겠지만, 그들이 수평선 너머로 사라지자마자 이상한 일들이 날씨에 일어나기 시작했지. 그때까지 며칠 동안 날씨가 아주 좋았거든, 구름 한 점 없었어! 그런데 이 끔찍한 폭풍이 갑자기 어디선가 나타난 거야. 마치 넵튠 신이 직접 우리를 찾아온 것 같았다니까! 나는 등대를 밝히려고 꼭대기로 올라갔는데, 그때 그녀를 봤어... 산타 키테리아! 거대한 파도 위로 솟구치고 있었고, 거대한 토네이도와 함께였지! 프리깃함이 내 등대 옆을 불꽃처럼 스쳐 지나가더니 폭풍에 휩쓸려 북서쪽으로 밀려갔어! 그 이후로 산타 키테리아를 본 사람은 아무도 없어. 한 시간쯤 지나니 바람도, 비도, 구름도 사라지고 해가 쨍쨍하게 떴지, 폭풍의 흔적은 하나도 없었어! 이런 일은 처음이야! 그래도 그날 내 만에서 호박을 엄청나게 주웠지...\n";
			link.l1 = "그래서 폭풍 때문에 프리깃이 다시 카리브 해로 돌아온 건가?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "그래! 저 멀리 마르티니크 쪽으로 갔지. 디초소가 그 폭풍을 버텼을 것 같진 않아, 그래도 정말 최선을 다하긴 했어! 프리깃은 가라앉지 않았지만, 산타 키테리아는 지금쯤 산호 사이 바다 밑에 있을 거야... 사실, 너는 나한테 디초소랑 그의 프리깃에 대해 물어본 첫 번째 사람이 아니야.";
			link.l1 = "정말이야? 미겔에게 관심 있던 다른 사람은 누구였지?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "스페인 함대의 멋진 선장이라더군! 자기소개를 했는데... 아, 이놈의 기억력... 아! 나리 디에고였어. 이름이 디에고였고, 성은... 데 몬타냐나 데 몬토야였지. 뭐 그런 식이었어. 너처럼 내 말을 들어주고, 고맙다 하고는 가버렸어. 그 뒤로는 본 적 없어.";
			if (sti(Pchar.money) >= 5000)
			{
				link.l1 = "알겠소. 이야기 정말 고맙소, 큰 도움이 되었소. 이 동전으로 내 감사의 뜻을 받아주시오. 안녕히 가시오.";
				AddMoneyToCharacter(pchar, -5000);
				AddCharacterExpToSkill(pchar, "Leadership", 250);
			}
			else
			{
				link.l1 = "알겠소. 이야기해 줘서 정말 고맙소, 큰 도움이 되었소. 안녕히 가시오.";
			}
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			AddQuestRecord("Guardoftruth", "41");
			pchar.questTemp.Guardoftruth.Trinidad = "mayak";
			pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
