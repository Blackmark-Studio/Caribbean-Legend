// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있습니까?","무엇을 도와드릴까요?"),"그 질문을 얼마 전에 나에게 하려고 했었지...","그래, 맞지... 또 뱅뱅 도는 거야?","이봐, 여기서 재정은 내가 맡고 있어, 질문엔 대답 안 해...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소...","지금은 할 말이 없소."),"음, 내 기억이 다 어디로 갔지...","눈치챘군, 미안하오...","알겠습니다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// Реакция ростовщика Панамы на репутацию ГГ или на разграбление Картахены по сюжету
		case "Panama_Deposit_NoReputation":
			dialog.text = "맞습니다... 국왕의 신민들에게 사랑받는 명예로운 분이라면, 국적이 무엇이든 저희 은행에서 결코 거절하지 않을 것입니다.";
			link.l1 = "알겠습니다. 안녕히 가십시오.";
			link.l1.go = "exit";
		break;
		
		case "Panama_Deposit_Cartahena":
			dialog.text = "하지만 내 딸과 장인은 불행히도 그 병에 걸렸어. 그들은 카르타헤나에 살았지. 가라, "+GetAddress_Form(NPChar)+". 여기는 당신을 환영하지 않소.";
			if (pchar.questTemp.Mtraxx.Retribution.Choice == "good")
			{
				link.l1 = "용서하십시오. 안녕히 가십시오.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "당신 손해지. 안녕히 가시오.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
		
		case "Panama_Deposit_SgorelVklad":
			dialog.text = "자금은 카르타헤나 시 약탈의 피해자들을 돕기 위해 국왕이 압수해 갔소. 나는 도와줄 수 없소. 경비병을 부르기 전에 즉시 내 은행에서 나가 주시오!";
			link.l1 = "이 일, 곧 후회하게 될 거야...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NeHochuRazgovarivat";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
