void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "이건 버그야. 개발자들에게 알려 줘.";
			link.l1 = "물론이지!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Wine_fort":
			dialog.text = "병 가져왔어?";
			if (CheckCharacterItem(pchar, "potionwine"))
			{
				link.l1 = "그래, 내가 그랬지. 그걸 700페소 주고 샀으니, 너한테는 1,000페소 받아야겠다.";
				link.l1.go = "Wine_fort_1";
			}
			link.l2 = "아니, 아직 처리 중이야.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort";
		break;
	
		case "Wine_fort_1":
			AddMoneyToCharacter(pchar, 1000);
			RemoveItems(PChar, "potionwine", 1);
			dialog.text = "신의 은총이로다, 목이 타들어 가던 참이었어. 정말 고맙소, 나리! 자, 여기 천 페소니 병은 내가 가져가겠소, 하하! 이봐, 이미 이렇게 좋은 거래를 했으니, 부탁 하나 더 하지\n나와 내 친구들을 위해... 앞으로 쓸 와인을 좀 더 구해줄 수 있겠나? 방금 밀수꾼들을 털어서 동전이 남아돌거든, 헤헤...";
			link.l1 = "미안하다, 친구. 너 술 심부름 또 해줄 시간 없어.";
			link.l1.go = "Wine_fort_exit";
			link.l2 = "돈이라면 언제나 환영이지. 병이 몇 개나 필요해?";
			link.l2.go = "Wine_fort_2";
		break;
	
	case "Wine_fort_exit":
			DelLandQuestMark(npchar);
			WineTraderQMDel();
			dialog.text = "원하시는 대로 하겠습니다. 어쨌든 도와주셔서 감사합니다! 건배, 그리고 건강을 기원합니다!";
			link.l1 = "계속 잘해라, 병사!";
			link.l1.go = "exit";
			sld = characterFromId(pchar.questTemp.Wine.id);	
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			pchar.questTemp.Wine.fail = "true";
			CloseQuestHeader("Wine");
	break;
	
		case "Wine_fort_2":
			dialog.text = "한 병에 1,000 에잇씩이면, 우리 예산으로는 예순 병까지 살 수 있지, 그 이상은 안 돼. \n하지만 열 병보다 적게 가져오진 마라—그러면 오히려 더 목마르겠으니까!";
			link.l1 = "알겠습니다, 60병을 넘지 않고 10병보다 적지 않게 준비하겠습니다. 당신의 와인을 가져오겠소.";
			link.l1.go = "Wine_fort_3";
		break;
	
		case "Wine_fort_3":
			dialog.text = "좋은 술 소식을 전해 오는 발걸음은 복이 있지! 자네를 믿고 있네, 선장. 아, 깜빡할 뻔했군! 술은 일주일 안에 여기로 가져와야 하네. 내 해병 부대가 7일 뒤 함대로 교대 배치될 예정이라, 우리가 떠나면 몇 달은 돌아오지 못할 테니까.";
			link.l1 = "알겠어. 빨리 해볼게.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.bottles = "true";
			npchar.lifeday = 7;
			AddQuestRecord("Wine", "1");
			AddQuestUserData("Wine", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Wine.City+"Gen"));
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.SName);
			SetFunctionTimerCondition("Soldier_wait", 0, 0, 7, false);
			NextDiag.TempNode = "Wine_fort_check";
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
	
		case "Wine_fort_check":
			dialog.text = "그래서, 선장님, 술 가져왔소?";
			if (sti(pchar.items.potionwine) >= 10)
			{
				link.l1 = "그래, 있다.";
				link.l1.go = "Wine_take";
			}
			link.l2 = "아니. 아직 작업 중이야.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_take":
			pchar.questTemp.Wine.Qty = sti(pchar.items.potionwine);
			pchar.questTemp.Wine.Money = sti(pchar.questTemp.Wine.Qty)*1000;
			if (sti(pchar.items.potionwine) > 60)
			{
				dialog.text = "성 아르눌프여, 우리를 위해 기도해 주십시오! 와인이 정말 많군! 훌륭하오! 유감스럽게도, 내가 말했듯이 우리는 겨우 예순 병만 살 수 있소; 아쉽게도 더 살 돈이 없소. 페소는 가져가시오, 이 예순 병은 내가 잘 보관하겠소. 나머지는 그냥 두시오.";
				link.l1 = "고맙네. 자네와 군인 친구들이 내 건강을 위해 꼭 한잔 올려주게!";
				link.l1.go = "Wine_take_1";
				pchar.questTemp.Wine.Money = 60000;
				RemoveItems(PChar, "potionwine", 60);
			}
			else
			{
				dialog.text = "돌아왔군. 어디 보자... 네가 가져온 것은 "+sti(pchar.questTemp.Wine.Qty)+" 병들이군. 좋아! 내가 가져갈게. 대금은\n "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Money))".";
				link.l1 = "고맙소. 자네와 군인 친구들이 내 건강을 위해 한 잔 올려주게나!";
				link.l1.go = "Wine_take_1";
				RemoveItems(PChar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			}
		break;
	
		case "Wine_take_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.Wine.Money));
			dialog.text = "물론 그렇게 하지. "+GetAddress_Form(NPChar)+"! 집합 북이 울리고 있어, 이제 가야 해. 잘 있어!";
			link.l1 = "순풍과 잔잔한 바다를 빌어, 친구!";
			link.l1.go = "Wine_take_2";
		break;
	
		case "Wine_take_2":
			DelLandQuestMark(npchar);
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info ("You handed over the wine");
			pchar.quest.Soldier_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.City");
			sld = characterFromId(pchar.questTemp.Wine.id);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
