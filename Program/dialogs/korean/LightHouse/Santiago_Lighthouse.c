// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("뭘 원하지?","무엇을 알고 싶은가?"),"무슨 일로 왔나, "+GetAddress_Form(NPChar)+"?","그거 세 번째로 나한테 물어보는 거야...","너 때문에 진절머리 나니까, 꺼져!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("미안, 마음이 바뀌었어.","별일 아니오, 미안하오."),"잊어버렸어, 미안해...","세 번째면 행운이 따르겠지, 응? 실례하네...","미안, 미안! 그럼 내가 나갈게...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
			{
				link.l1 = "안녕하시오. 산티아고의 종교재판관인 빈센토 신부께서 편지에서 자네를 언급했소. 자네가 나를 도와줄 수 있을 거라고 하더군.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
			{
				link.l1 = "Vincento 신부 소식 있나? "+npchar.name+"?";
                link.l1.go = "guardoftruth_5";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
			{
				link.l1 = "나는 Vincento 신부를 만나야 해. 그가 관심 있어 하는 물건들을 찾았거든.";
                link.l1.go = "guardoftruth_7";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
			{
				link.l1 = "그래, "+npchar.name+", 빈첸토 신부가 너한테 뭐라고 했지?";
                link.l1.go = "guardoftruth_11";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "물론이오, 나리. 빈첸토 신부님이 직접 당신과 거래를 한다면 분명 명성이 높은 분이겠지.";
			link.l1 = "훌륭하군. 이제 네가 우리 심부름꾼이야. 잘 들어, 이 자는 빈첸토 신부께서 크게 관심을 두고 계신 인물이야. 이제 네가 책임져야 하니, 산티아고로 직접 데려가든가, 아니면 대신 데려갈 사람을 찾아야 해.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "...";
			link.l1 = "너는 종교재판관을 대신해서 그 죄수를 책임져야 해. 족쇄를 풀지 않는 게 좋을 거야, 가이우스 마르셰는 힘이 센 놈이거든. 이 편지를 빈첸토 신부에게 전해 주고, 이틀 안에 답장을 기다린다고 전해 줘. 이 정도면 충분할 거라 생각한다.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			Log_Info("You part with the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "알겠소, 나리. 최선을 다하겠소. 신부님을 돕는 게 이번이 처음은 아니오.";
			link.l1 = "그게 다가 아니야. 산 그레고리오의 카라카 선장, 카를로스 게바라가 여기 왔던 게 틀림없어. 그가 나한테 바닐라를 가져다줬거든. 내 편지를 너한테 전해줬냐?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "그래, 네 화물은 멀쩡하게 잘 보관돼 있고 기다리고 있어, 나리.";
			link.l1 = "좋아, 그럼 내 배로 실어 놓도록 하지. 나는 이틀 동안 여기 머물면서 빈첸토 신부님의 답을 기다릴 거야. 그러니 지금은 작별이 아니야. "+npchar.name+"!";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			LocatorReloadEnterDisable("mayak9", "boat", false);
			ref sld = characterFromId("GOT_Marshe");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakNextStage", 0, 0, 2, false);
			SetCharacterGoods(pchar, GOOD_CINNAMON, GetCargoGoods(pchar, GOOD_CINNAMON) + sti(pchar.questTemp.Guardoftruth.VanilleQty));
			AddQuestRecord("Guardoftruth", "21");
		break;
		
		case "guardoftruth_5":
			dialog.text = "그래, 나리. 여기 빈센토 신부님께서 보내신 편지가 있소. 신부님께서 당신을 무척 기뻐하셨소, 나머지는 편지를 읽어보면 알게 될 것이오.";
			link.l1 = "훌륭하군. 그때까지, "+npchar.name+". 그리고 지금은 - 안녕히 가시오.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_exit";
			GiveItem2Character(pchar, "specialletter");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_next";
		break;
		
		case "guardoftruth_7":
			dialog.text = "알겠소. 그것들을 내게 주면 내가 교황님께 가져가겠소.";
			link.l1 = "말도 안 돼, 이봐! 그거 구하는 게 얼마나 힘들었는데 그냥 줄 수는 없어. 나는 오직 빈첸토 신부에게 직접 줄 거야.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "하지만 나리! 내가 속임수에 넘어가지 않는다는 걸 어떻게 알 수 있소?";
			link.l1 = "한번 봐봐: 향로, 성배, 그리고 청금석이 박힌 십자가야... "+npchar.name+", 내가 누군지 아냐? 내가 그 사람들 없이 종교재판소에 갈 만큼 어리석다고 정말 생각해?";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "용서하시오, 나리... 내일 다시 오면 비센토 신부에게 당신이 온 걸 전하겠소.";
			link.l1 = "좋아. 내일 보자.";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;
		
		case "guardoftruth_11":
			dialog.text = "그분께서 당신을 맞이하실 거요, 나리. 방문을 미루지 마시오. 여기 문서가 있으니, 경비병들에게 보여 주면 들여보내 줄 거요. 하지만 먼저 스페인 깃발을 올리시오, 그렇지 않으면 병사들이 당신을 체포할지도 모르니.";
			link.l1 = "알겠어. 그럼 스페인 놈들이군. 고마워, 친구! 이제 간다!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper");
			pchar.questTemp.Guardoftruth = "santiago";
			AddQuestRecord("Guardoftruth", "34");
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 400);//скрытность
			GuardOT_SetPadreVincento();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
