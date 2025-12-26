// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("모든 소문이 "+GetCityName(npchar.city)+" 항상 대기 중이오. 무엇을 알고 싶으시오?","바로 그 얘기를 하고 있었지. 네가 잊어버린 모양이군...","오늘만 세 번째로 그 질문을 꺼내는군...","앵무새처럼 똑같은 말만 반복하네...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 아마 다음에.","그래, 무슨 이유에선지 잊어버렸네...","그래, 진짜로 이번이 세 번째야...","그래...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "혹시 프랑수아 곤티에가 어디 있는지 아시오?";
                link.l1.go = "Jamaica_ratP_1";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "이봐, 이 마을에 연금술사나 의사가 온 적 있나? 이탈리아 사람이고, 서른 살쯤 된 남자야. 이름은 지노 그비네일리라고 해. 그에 대해 들은 거 있어?";
				link.l1.go = "guardoftruth";
			}
		break;

		case "Jamaica_ratP_1":
			dialog.text = NPCStringReactionRepeat("나는 전혀 모르겠어. 그 이름은 들어본 적도 없어.","그건 이미 물어봤고 내가 대답했잖아.","이미 말했잖아, 그건 벌써 물어봤다구, Gontier.","이봐, 그냥 가서 그만 귀찮게 해! 완전히 미친 거 아니야?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("그렇다면, 계속 찾아보겠소.","흠, 그렇겠지...","그래, 맞아, 내가 그렇게 부탁했지...","미안하다, "+npchar.name+"...",npchar,Dialog.CurrentNode);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("아니, 못 봤어. 약초사랑 의원들은 있지만, 그 이름을 가진 사람은 없어.","이렇게 이상한 이름은 처음 들어보네. 아니, 네가 말한 그 남자는 우리한테 온 적 없어.","여기엔 연금술사 같은 건 전혀 없어. 의사는 있지만, 그런 이상한 이름 가진 사람은 없어.");
			link.l1 = "알겠어. 아쉽군. 계속 찾아볼게!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
