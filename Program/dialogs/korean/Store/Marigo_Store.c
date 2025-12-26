// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("어서 말해라, 무엇을 원하는가?","바로 그 얘기를 하고 있었소. 당신이 잊어버린 모양이군...","오늘만 벌써 세 번째로 그 질문을 꺼내는군...","이봐, 여긴 상점이야. 사람들은 여기서 물건을 사지. 나 좀 방해하지 마!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 아마 다음 기회에.","맞아요, 무슨 이유에선지 잊고 있었군요...","그래, 정말 이번이 세 번째야...","흠, 나는 안 하겠어...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason --> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Findcloves" && !CheckAttribute(npchar, "quest.Portugal"))
			{
   				link.l1 = "이봐, 근사한 옷이 좀 필요해. 값비싼 걸로, 제대로 된 귀족처럼 보이고 싶거든. 그런 옷 있나?";
				link.l1.go = "Portugal_cloves";
			}
			//<-- Португалец
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten")
			{
				link.l1 = "'Admirable'이라는 이름의 갤리온이 최근에 가죽 화물을 당신에게 가져왔지요. 그것을 기억하십니까?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		//Jason --> Португалец
		case "Portugal_cloves":
			dialog.text = "귀족 옷이냐고? 물론이지, 여기 한 벌 있어. 바지, 저킨, 비단 셔츠, 그리고 부츠까지. 2만 페소야. 옷은 아주 고급스럽고, 입기도 편하며, 외관도 뛰어나니 그 이하로는 못 팔아.";
			if (sti(pchar.money) >= 20000)
			{
				link.l1 = "좋아! 내놔.";
				link.l1.go = "Portugal_cloves_1";
			}
			link.l2 = "흠... 지금은 그 정도 돈이 없어.";
			link.l2.go = "Portugal_cloves_nomoney";
		break;
		
		case "Portugal_cloves_nomoney":
			dialog.text = "돈을 마련하면 다시 오시오.";
			link.l1 = "알겠소. 곧 돌아오겠소!";
			link.l1.go = "exit";
		break;
		
		case "Portugal_cloves_1":
			AddMoneyToCharacter(pchar, -20000);
			GiveItem2Character(pchar, "suit_1");
			Log_Info("You've received expensive clothing");
			PlaySound("interface\important_item.wav");
			dialog.text = "여기 있습니다.";
			link.l1 = "감사합니다!";
			link.l1.go = "exit";
			npchar.quest.Portugal = "true";
			sld = characterFromId("PortugalDoctor");
			sld.dialog.currentnode = "Portugal_doctor_4";
			DelLandQuestMark(characterFromId("Marigo_trader"));
			AddLandQuestMark(characterFromId("PortugalDoctor"), "questmarkmain");
			QuestPointerDelLoc("marigo_town", "reload", "reload6_back");
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		//<-- Португалец
		case "guardoftruth":
			dialog.text = "예. 그는 제시간에 도착해서 물건을 내렸고, 우리는 약속한 대로 대금을 치렀소. 왜 묻는 것이오?";
			link.l1 = "저 배의 선장은 가이우스 마르셰라는 제 오랜 지인입니다. 그래서 그를 찾고 있지요. 혹시 그 후에 그가 무엇을 했는지 말씀해 주실 수 있겠습니까? 혹시 추가로 화물을 실어 주셨거나, 어디로 간다고 언급한 적이 있습니까?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "그런 일은 없었소. 나는 그에게 화물을 제안한 적도 없고, 그는 그것을 요구하지도 않았소. 그는 앞으로의 계획에 대해 나와 아무것도 공유하지 않았소. 모든 세부사항을 다 기억하지도 못하오, 그때 이후로 이곳을 드나든 사람이 얼마나 많은지 아시오? 그는 짐을 내리고 떠났소, 내가 그에 대해 말할 수 있는 건 그게 전부요.";
			link.l1 = "알겠소. 그래도 고맙소. 행운을 빌겠소!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "11");
			pchar.questTemp.Guardoftruth = "maarten1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
