// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "말해 봐라, 듣고 있다";
			link.l1 = "내가 착각했군. 잘 가라.";
			link.l1.go = "Exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "여기서 역병이 돌고 있다고 들었는데, 맞소?";
				link.l1.go = "Consumption";
			}
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "맞는 말이오, 그러니 별다른 이유 없이 지하 감옥에 들르지 마시오. 그런데 왜 이것에 관심이 있소?";
			link.l1 = "그냥 궁금해서 묻는 거야. 내 부하들이 술에 너무 취해서 시끄럽게 굴다가 여기 끌려오면, 내가 노란 수의를 준비해야 하겠군?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "안타깝게도, 나리, 농담하신 거라면 난 그 농담을 이해하지 못하겠소. 지하 감옥은 눅눅하고 춥소, 이 기후는 당신도 알 테지. 결핵이 이 감옥의 단골손님이오. 내 부하들에게 방에 음식을 가져다주라고 추가로 돈까지 줘야 하오. 그곳을 순찰하는 건 유배형만큼이나 고된 일로 여겨지지.";
			link.l1 = "미안하오, 그냥 이 일이 얼마나 심각한지 알고 싶었을 뿐이오?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "너무 심각하지. 여기엔 의사도 없어. 그 자도 저주받은 폐병으로 죽었거든. 이제는 지역 주둔지에서 온 위생병이 일주일에 한 번 죄수들을 검사할 뿐이야. 하지만 이런 부랑자나 범죄자 따위, 누가 신경이나 쓰겠나?\n대부분 사람들은 저놈들이 그런 운명을 당해도 마땅하다고 생각하지. 그걸 반박하기도 힘들고.";
			link.l1 = "내 의학 지식은 부족하지만, 내가 알기로 폐병은 위험하고 치명적이긴 해도 여기처럼 며칠 만에 사람을 죽이지는 않소. 원래라면 피해자들이 몇 달, 아니면 몇 년 동안 고통받아야 하지 않소?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "방금 말했듯이, 자네는 의사가 아니니 그 병의 특징에 대해 말하는 건... 그냥 지어낸 거짓말일 뿐일 수도 있지. 나는 단지 우리 의원이 병에 걸려 죽기 전에 했던 말을 반복했을 뿐이야. 그러니 자네의 호기심과 냉소적인 태도를 이해할 수 없군. 여기서는 사람들이 죽어나가고 있어!";
			link.l1 = "방금 그들이 당해도 마땅하다고 하지 않았나?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "그만하시오, 나리! 자네와 나는 재치 겨룰 시간보다 처리할 다른 일이 있을 것이오. 문은 바로 뒤에 있소.";
			link.l1 = "좋소, 내 무례함을 용서하시오, 이미 떠나겠소.";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			DialogExit();
			npchar.quest.Consumption = "true";
			pchar.questTemp.Consumption.Commandant = "true";
			AddQuestRecord("Consumption", "3");
			pchar.quest.Consumption.win_condition.l1 = "location";
			pchar.quest.Consumption.win_condition.l1.location = "PortSpein_houseF2";
			pchar.quest.Consumption.function = "Consumption_CommandantHouse";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
