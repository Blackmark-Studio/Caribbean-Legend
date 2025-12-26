// старпом Акулы - Лейтон Декстер
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "귀찮게 하지 마, 꼬마야. 여기서는 샤크가 책임자니까 그에게 말해.";
				link.l1 = "적어도 인사는 해도 되겠소, 아니면 그것도 규칙에 어긋나는 거요?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(npchar, "quest.map"))
				{
					link.l2 = "레이튼, 샤크가 너한테 정의의 섬 지도 있다고 하던데. 그거 나한테 팔 수 있겠어?";
					link.l2.go = "map";
				}
				dialog.text = "아, "+GetFullName(pchar)+"! 나한테 볼일이 있나, 아니면 그냥 얘기나 하러 온 건가? 뭐든 상관없으니, 다음엔 럼 한 병 들고 오라고, 하하!";
				link.l1 = "아니, 그냥 인사하고 싶었어. 다음엔 너만을 위해 럼주를 가져올게.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "하! 농담쟁이로군! 좋아... 내 이름은 레이턴 덱스터야. 여기 떠밀려오기 전엔 샤크의 부선장이었고, 지금은 이 '버려진 배들의 도시'에서 그의 부하로 일하고 있지. (침을 뱉는다)\n요즘은 주민들에게 식량을 팔면서 게으름뱅이 파지오에게서 돈을 뜯어내려고 애쓰고 있어.";
			link.l1 = "나는 "+GetFullName(pchar)+"... 만나서 반갑군. 그런 것 같아.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Акула погиб по варианту N
		case "admiral":
			dialog.text = "이미 스티브가 죽었다는 소문 들었겠지. 그건 전부 나르발 놈들 짓이야.";
			link.l1 = "들었어... 그래서, 네가 새로운 제독이란 말이지?";
			link.l1.go = "admiral_1";
			AddQuestRecord("SharkHunt", "28");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition	
		break;
		
		case "admiral_1":
			dialog.text = "그래. 챈드는 나르발 쪽으로 넘어갔고, 스티브는 죽었으니... 내가 제독이다. 불만 있나?";
			link.l1 = "아니... 이의 없어.";
			link.l1.go = "admiral_2";
		break;
		
		case "admiral_2":
			dialog.text = "좋아.";
			link.l1 = "상어의 죽음 때문에 너, 혹시 나르발들에게 복수할 생각이야?";
			link.l1.go = "admiral_3";
		break;
		
		case "admiral_3":
			dialog.text = "그러니까, 내가 그들에게 전쟁을 선포할 거냐고? 아니. 그들에게 대가를 치르게 할 더 좋은 방법이 있지.\n먼저, 식량값을 세 배로 올릴 거야. 그게 마음에 안 들어서 산 아우구스틴을 공격하려 든다면, 피로 값을 치르게 해주지.\n다음엔 리바도스와 휴전을 협상할 생각이야. 물론, 그 더러운 흑인 놈들을 믿을 수는 없지, 특히 그들의 주술사 치미셋이 죽은 뒤로는 더더욱. 하지만 음식과 럼주라면 어떤 죄도 덮을 수 있거든.";
			link.l1 = "알겠어. 그럼... 잘 가, 레이튼...";
			link.l1.go = "admiral_4";
		break;
		
		// нода пересечения
		case "admiral_4":
			dialog.text = "잠깐. 스티브가 네가 정의의 섬을 떠나 배를 가지고 돌아오고 싶어 한다고 말했어. 아직도 그게 네 계획이야?";
			link.l1 = "그렇소.";
			link.l1.go = "admiral_5";
		break;
		
		case "admiral_5":
			dialog.text = "이 항해 지침서를 가져가. 여기엔 네가 무사히 다시 정의의 섬으로 돌아올 수 있는 항로가 적혀 있어. 암초에 걸리지도 않고, 조류에 휩쓸리지도 않으며, 바깥쪽 난파선들과도 부딪히지 않게 말이지.\n이게 없으면 섬을 아예 지나치거나, 또 하나의 난파선 신세가 될 거야.\n암초 사이를 지나려면 반드시 흘수선이 얕은 작은 배를 써야 해. 타르탄, 러거, 스쿠너, 슬루프... 더 큰 배는 안 돼. 알겠지?";
			link.l1 = "그래, 알아. 고맙다.";
			link.l1.go = "admiral_6";
		break;
		
		case "admiral_6":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "화물창에 식량을 가득 채우는 거 잊지 마. 내가 좋은 값에 사줄 테니까. 그리고 이 문서는 절대 아무에게도 보여주지 마라. 우리 기지는 반드시 비밀로 남아야 해. 내가 이걸 주는 건 스티브 본인이 직접 줄 생각이었고, 네가 얀 스벤손의 친구이기 때문이야.";
			link.l1 = "이것들을 다른 누구에게도 보여주지 않겠다고 약속할게. 다시 한 번 고마워, 레이턴.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
			AddQuestRecord("LSC", "5");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dexter_wait":
			dialog.text = "탈출 계획은 좀 진전됐나, "+pchar.name+"?";
			link.l1 = "아직이야, Layton, 내가 처리하고 있어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
		break;
		
		// Акула погиб по варианту M
		case "admiral_7":
			dialog.text = "여기 있었군. 우리 얘기 좀 해야겠어.";
			link.l1 = "그래서 이제 네가 제독이란 말이야?";
			link.l1.go = "admiral_8";
		break;
		
		case "admiral_8":
			dialog.text = "그래, 내가 제독이다. 스티브랑 모든 걸 함께한 동료였으니 그가 죽고 나서 내가 책임을 맡게 됐다. 불만 있나?";
			link.l1 = "아니... 이의 없어. 그럴 권리 충분히 있지.";
			link.l1.go = "admiral_9";
		break;
		
		case "admiral_9":
			dialog.text = "서로 이해하게 되어 다행이군. 필요한 게 있으면 말해.";
			link.l1 = "상어의 죽음 때문에 너, 혹시 나르발들에게 복수할 생각이야?";
			link.l1.go = "admiral_10";
		break;
		
		case "admiral_10":
			dialog.text = "그러니까, 내가 그들에게 전쟁을 선포할 거냐고? 아니. 그들에게 대가를 치르게 할 더 좋은 방법이 있지.\n먼저 식량값을 세 배로 올릴 거야. 그게 마음에 안 들어서 산 아우구스틴을 공격하려 든다면, 피로 값을 치르게 해주지.\n게다가 지금은 리바도스와도 좋은 관계를 맺고 있으니, 나르발들이 다시 우리에게 덤비는 걸 망설일 거야.";
			link.l1 = "알겠어. 더 할 말 있어, 아니면 가도 돼?";
			link.l1.go = "admiral_4";
		break;
		
		case "plan":
			PlaySound("Voice\English\LSC\Layton Dexter-07");
			dialog.text = "그래. 우리가 나르발들에게 접근할 수 있는 방법은 하나뿐인 것 같아. 완벽하진 않지만, 다른 대안이 보이지 않아.\n한 무리는 롱보트를 타고 세레스에 올라타고, 다른 무리는 리바도스와 합세해서 에스메랄다를 습격할 거야.\n이렇게 하면 그놈들을 완전히 없애버리거나, 아니면 산 가브리엘로 도망치게 만들 수 있지.\n두 번째 경우가 더 가능성 높아. 산 가브리엘은 방어하기 좋은 위치라 포위하려면 오래 걸릴 거야. 어느 쪽이든 우리가 이기는 셈이지.";
			link.l1 = "";
			link.l1.go = "plan_1";
		break;
		
		case "plan_1": // ноду Акуле
			DialogExit();
			npchar.greeting = "dexter_1";
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "whyskey_final_3";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			NextDiag.CurrentNode = "plan_2";
		break;
		
		case "plan_2":
			dialog.text = "나는 자네가 도널드 그린스팬과 나눈 대화 보고를 기다리고 있네. 이건 매우 중요한 일이니, 시간 낭비하지 말게.";
			link.l1 = "가는 중이야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "plan_2";
		break;
		
		case "map":
			dialog.text = "그래, 나한테 지도 있어. 원한다면, 이백 두블룬만 주면 네 것이 될 수 있지.";
			link.l1 = "페소는 어때?";
			link.l1.go = "map_1";
		break;
		
		case "map_1":
			dialog.text = "아니, 나는 금화만 받는다 - 흥정해 봐야 소용없어. 이 지도가 얼마짜리인지 정확히 알고 있으니까, 이백 두블룬이야.";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "좋아, 동의하지. 여기 네 금화다.";
				link.l1.go = "map_2";
			}
			link.l2 = "나한테 그만한 금화는 없어. 나중에 혹시...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "map_2":
			RemoveDublonsFromPCharTotal(200);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a map of the City of Abandoned Ships");
			GiveItem2Character(pchar, "map_LSC");
			dialog.text = "지도 가져가. 값어치는 충분해 – 내가 이거 그리려고 도시를 꼬박 일주일이나 기어 다녔거든. 사실, 이 정도면 싸게 판 거라고 생각해.";
			link.l1 = "싸게?! 하! 뭐... 고맙다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "quest.map");
		break;
		
		// геймовер диким геймерам за издевательство над игрой
		case "LSC_GameOverPrison":
			dialog.text = "거기서 멈춰, 이봐! 그래, 샤크 말이 맞았어, 이 자식 완전히 미쳤군. 저놈 때문에 죽은 사람이 얼마나 많은데... 저놈을 묶어서 창고에 쳐넣어!";
			link.l1 = "...";
			link.l1.go = "LSC_GameOverPrison_1";
		break;
		
		case "LSC_GameOverPrison_1":
			DialogExit();
			DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
		break;
		
		case "return":
			dialog.text = "스티브가 자기 대신 나를 제독으로 임명했어 - 보아하니 너랑 스티브 둘이서 카리브 해로 돌아가는 거구나.\n나는 여기 남아서 계속 일을 볼 거야. 나랑 스티브 둘 다 이렇게 좋은 근거지를 잃고 싶진 않거든. 그리고 너야말로, 물론 언제든 여기서 환영받는 손님이지.";
			link.l1 = "고마워, 레이튼. 저 수평선을 잘 지켜봐. 언젠가 내가 돌아올 테니까.";
			link.l1.go = "return_1";
		break;
		
		case "return_A":
			dialog.text = "아하, "+GetFullName(pchar)+"! 해냈구나! 스티브의 항해 지침을 따라 정의의 섬을 찾은 거지? 미친 놈... 돌아온 걸 환영한다!";
			link.l1 = "고마워, 레이튼. 언젠가 다시 올 거라고 했잖아, 하하!";
			link.l1.go = "return_1";
		break;
		
		int iTrade = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
		int iMoney = 0;
		case "return_1":
			dialog.text = "좋아. 혹시 팔 만한 음식이 있나? 시세의 두 배로 살 준비가 되어 있어.";
			if (iTrade > 0)
			{
				link.l1 = "그래, 식량을 팔고 있지.";
				link.l1.go = "trade";
			}
			link.l2 = "안타깝게도, 지금은 당신에게 팔 것이 없어.";
			link.l2.go = "return_2";
			npchar.quest.foodqty = 0; // предел затарки складов = 15 000
		break;
		
		case "return_2":
			dialog.text = "안타깝군. 다음엔 꼭 좀 가져와. 값은 제대로 쳐줄 테니.";
			link.l1 = "잊지 않도록 노력할게.";
			link.l1.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "trade":
			dialog.text = "얼마야?";
			link.l1.edit = 4;
			link.l1 = "";	
			link.l1.go = "trade_1";
		break;
		
		case "trade_1":
			iTemp = dialogEditStrings[4];
			int iMax = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
			if (iTemp <= 0 || iTemp > GetSquadronGoods(pchar, GOOD_FOOD))
			{
				dialog.text = "뭐야, 취했냐, 이봐? 진지하게 얘기할 준비되면 다시 와.";
				link.l1 = "흠...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp <= 50)
			{
				dialog.text = "그건 푼돈이야! 내 시간 낭비할 가치도 없어 - 더 많이 가져와!";
				link.l1 = "흠...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp > iMax)
			{
				dialog.text = "그런데 식량도 없이 어떻게 항해할 생각이야, 이봐? 네 놈 부하들 굶기고 싶어? 최소한은 챙겨둬야지 "+FindRussianQtyString(GetCrewQuantity(pchar))+".";
				link.l1 = "어, 네 말이 맞아.";
				link.l1.go = "exit";
			break;
			}
			if (iTemp >= 15000) // лесник
			{
			 iTemp = (15000 - sti(npchar.quest.foodqty))	
             dialog.text = "예수 그리스도, 그건 우리한테 너무 많아! 저렇게 많으면 상하기 전에 절대 다 못 먹지. 지금은 더 이상 받을 수 없어 "+iTemp+".";
			 link.l1 = "알겠소.";
			 link.l1.go = "trade_3";
			 break;
            }							  
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = ""+FindRussianQtyString(iTemp)+"? 좋아, 돈 줄게 "+FindRussianMoneyString(iMoney)+". 거래지?";
			link.l1 = "거래 성사! 함께 일해서 좋았어!";
			link.l1.go = "trade_2";
			link.l2 = "음... 아니, 마음이 바뀌었어.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_3": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
		    iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = "거래지. 내가 돈 줄게 "+FindRussianMoneyString(iMoney)+" 물건값으로. 공정하지?";
			link.l1 = "공정하군! 거래해서 좋았어!";
			link.l1.go = "trade_4";
			link.l2 = "흠... 아니, 마음이 바뀌었어.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_4": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "제기랄! 내 창고가 꽉 찼군! 앞으로 반년은 식량을 살 필요도 없겠어.";
				link.l1 = "좋아. 그럼 여섯 달 후에 다음 식량을 가져다줄게.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "좋아! 다음엔 더 가져와.";
				link.l1 = "물론이지!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		case "trade_2":
			iTemp = dialogEditStrings[4];
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "훌륭하군! 이제 내 창고가 가득 찼어. 앞으로 반년 동안은 식량을 살 필요가 없겠어.";
				link.l1 = "좋아. 그럼 여섯 달 후에 다음 식량을 가져오지.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "좋아! 다음엔 더 가져와.";
				link.l1 = "물론이지!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		
		case "head": // стандартный диалог Декстера-адмирала
			dialog.text = "아-아, "+GetFullName(pchar)+"! 반갑군! 무슨 일이야?";
			if (iTrade > 0 && sti(npchar.quest.foodqty) < 15000)
			{
				link.l1 = "나한테 식량 좀 살래?";
				link.l1.go = "trade";
			}
			link.l2 = "별거 아니야, 그냥 어떻게 지내나 궁금해서 왔어.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
