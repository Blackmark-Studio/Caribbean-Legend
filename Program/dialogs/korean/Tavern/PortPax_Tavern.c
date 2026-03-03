// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("모든 소문이 "+GetCityName(npchar.city)+" 항상 대기 중이오. 무엇을 알고 싶으시오?","우리가 방금 그 얘기하고 있었잖아. 너 잊어버린 거 아냐...","오늘만 세 번째로 그 질문을 꺼내는군...","너, 앵무새처럼 똑같은 말만 반복하고 있잖아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 아마 다음에.","그래, 뭔가 이유가 있었는지 내가 잊어버렸군...","그래, 정말 이번이 세 번째야...","그래...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince")
			{
				link.l1 = "말해 봐, 'Santa Margarita'라는 이름의 갤리온이 최근에 너희 식민지에 들른 적 있나? 혹시 사략선의 전리품으로 말이야?";
                link.l1.go = "guardoftruth";
			}
			//--> Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogCitizen"))
			{
				link.l1 = "트리스탄 르니에가 최근에 여기 다녀갔나?";
				link.l1.go = "UV_DialogTavern";
			}
			//<-- Украденное воспоминание
		break;
		
		case "guardoftruth":
			dialog.text = "이봐, 우리 식민지에 전리품을 들고 오는 사람은 드물어. 그 이름의 갤리언은 본 적 없어. 히스파니올라는 거친 섬이고, 우리는 작은 식민지야. 여긴 조용하지. 고지대의 버커니어들과 소가죽이랑 육포를 거래해. 사략선들은 보통 오래 머물지 않아. 여기엔 사창가도 없고, 스페인 놈들도 가까이 있거든. 네 갤리언은 다른 데 가서 찾아봐.";
			link.l1 = "알겠어. 조언 고마워!";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "7");
			pchar.questTemp.Guardoftruth = "tortuga";
		break;
		
		//--> Украденное воспоминание
		case "UV_DialogTavern":
			dialog.text = "르니에? 그래, 여기 왔을 뿐만 아니라 아직도 안 떠났어. 방을 잡고 머무르고 있지.";
			link.l1 = "행운이 나에게 미소 짓는군! 훌륭한 선장과의 내 일은 지체할 수 없어—그의 사생활도 필요 앞에서는 양보해야지. 어느 방에 그가 있지?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RoomInTavern");
			DelLandQuestMark(npchar);
		break;
		//<-- Украденное воспоминание

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
