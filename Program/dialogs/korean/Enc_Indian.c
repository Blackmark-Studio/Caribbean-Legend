//Jason диалог индейцев в джунглях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iQty;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","백인 여자 인디언")+" 이야기하고 싶은가?","또 너냐, "+GetSexPhrase("창백한 얼굴","백인 여자")+".",""+GetSexPhrase("창백한 얼굴은 말이 많군. 여자처럼 보이네.","하얀 여자놈은 말이 많군.")+"","정령이 날 이끌었지, 창백한 얼굴 "+GetSexPhrase("형제.","누이")+".","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("그래.","그래, 또 나야.","참 시적이군.","나도 너를 다시 보게 되어 기쁘다.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "안녕, 백인 형제여. 인디언과 이야기하고 싶은가?";
				link.l1 = "정글의 아들이여, 반갑소. 만나서 기쁘지만, 나는 여정을 계속해야 하오.";
				link.l1.go = "exit";
				link.l2 = "그래. 흥미로운 물건을 판다고 들었어. 팔 만한 게 있나?";
				link.l2.go = "select_trade";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "select_trade": //индейская торговля
			switch (hrand(7))
			{
				case 0: // торговля через интерфейс
					dialog.text = "운이 좋군, 백인 형제. "+npchar.name+" 판매할 물건이 좀 있어. 한번 봐.";
					link.l1 = "물건 좀 보여줘...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "잠깐만. 팔 게 있어. 망가로사라는 식물이야. 이걸 좋아한다는 소문을 들었거든...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 1: // не торгует
					dialog.text = "아니, 백인 형제. "+npchar.name+" 거래하지 않아. "+npchar.name+"  전사다.";
					link.l1 = "알겠네. 좋아, 잘 가게, 붉은 피부의 형제여.";
					link.l1.go = "exit";
				break;
				
				case 2: // жемчуг большой
					npchar.quest.item.qty = 25+hrand(25);
					npchar.quest.item.price = 30+hrand(10);
					dialog.text = ""+npchar.name+" 신의 눈물이 있지. 큰 거야, 백인 형제. 그 양이 "+FindRussianQtyString(sti(npchar.quest.item.qty))+". 그걸 사고 싶어? 나는 가격이 "+FindRussianMoneyString(sti(npchar.quest.item.price))+" 일단.";
					link.l1 = "아니, 관심 없어.";
					link.l1.go = "exit";
					link.l2 = "물론이지! 그런 가격이라면 기꺼이 사겠어.";
					link.l2.go = "big_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "잠깐만. 팔 게 있어. 망가 로사라는 식물이야. 이거 좋아한다는 얘길 들었거든...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 3: // жемчуг малый
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 10+hrand(5);
					dialog.text = ""+npchar.name+" 신의 눈물이 있지. 작은 것들이야, 하얀 형제여. 그 양은 "+FindRussianQtyString(sti(npchar.quest.item.qty))+". 그걸 사고 싶어? 나는 \n에 판다 "+FindRussianMoneyString(sti(npchar.quest.item.price))+" 일단.";
					link.l1 = "아니, 난 관심 없어.";
					link.l1.go = "exit";
					link.l2 = "물론이지! 그런 가격이라면 기꺼이 사겠어.";
					link.l2.go = "small_pearl";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "잠깐만. 팔 게 있어. 망가 로사라는 식물이야. 이걸 좋아한다는 소문을 들었거든...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 4: //золотые самородки
					npchar.quest.item.qty = 20+hrand(20);
					npchar.quest.item.price = 90+hrand(20);
					dialog.text = ""+npchar.name+" 노란 금속이 있지, 너희 창백한 얼굴들이 아주 좋아하는 거 말이야. 그 양이 "+FindRussianQtyString(sti(npchar.quest.item.qty))+". 나는 오직 ~만 받고 판다 "+FindRussianMoneyString(sti(npchar.quest.item.price))+" 일단.";
					link.l1 = "아니, 나는 관심 없어.";
					link.l1.go = "exit";
					link.l2 = "물론이지! 그런 가격이라면 기꺼이 사겠다.";
					link.l2.go = "gold";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "잠깐만. 팔 게 있어. 망가 로사라는 식물이야. 이거 좋아한다는 소문을 들었거든...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 5: // серебряные самородки
					npchar.quest.item.qty = 40+hrand(40);
					npchar.quest.item.price = 40+hrand(10);
					dialog.text = ""+npchar.name+" 너희 백인들이 그렇게 좋아하는 흰 금속이 있지. 그 양이 "+FindRussianQtyString(sti(npchar.quest.item.qty))+". 나는 오직 ~에만 판다 "+FindRussianMoneyString(sti(npchar.quest.item.price))+" 하나로.";
					link.l1 = "아니, 관심 없어.";
					link.l1.go = "exit";
					link.l2 = "물론이오! 그런 가격이라면 기꺼이 사겠소.";
					link.l2.go = "silver";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "잠깐만. 팔 게 있어. 망가 로사라는 식물이야. 이걸 좋아한다는 얘기를 들었거든...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 6: // повтор через интерфейс
					dialog.text = "운이 좋군, 백인 형제. "+npchar.name+" 판매할 물건이 좀 있어. 한번 봐.";
					link.l1 = "물건 좀 보여줘...";
					link.l1.go = "torg";
					if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && !CheckAttribute(npchar, "quest.mangarosa"))
					{
						if (pchar.questTemp.Mangarosa == "gipsy" || pchar.questTemp.Mangarosa == "gipsy_trade")
						{
							link.l9 = "잠깐만. 팔 게 있어. 망가 로사라는 식물이야. 이거 좋아한다는 소문을 들었거든...";
							link.l9.go = "mangarosa";
						}
					}
				break;
				
				case 7: // повтор не торгует
					dialog.text = "아니, 백인 형제. "+npchar.name+"  거래하지 않는다. "+npchar.name+" -  전사다.";
					link.l1 = "알겠네. 좋아, 잘 가게, 붉은 피부의 형제여.";
					link.l1.go = "exit";
				break;
			}
		break;
		
		case "torg":
			DialogExit();
			if (CheckNPCQuestDate(npchar, "Torg_date"))
			{
                SetNPCQuestDate(npchar, "Torg_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = "First time";
			LaunchItemsTrade(NPChar, 0);
			ChangeIndianRelation(1.00);
		break;
		
		// большой жемчуг
		case "big_pearl":
			dialog.text = "눈물을 얼마나 사고 싶은가?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "big_pearl_qty";
		break;
		
		case "big_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "농담하나, 창백한 얼굴? 신들의 눈물이 필요 없단 말이지? 그럼 잘 가라.";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "내가 얼마나 많은 눈물을 흘렸는지 말했지. 인디언하고 농담하냐, 창백이? 그럼 잘 가라.";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" 눈물? 좋아. 그럼 네가 나한테 줘. "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", 백인 형제여.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "여기 네 돈이다, 붉은 피부 형제여.";
				link.l1.go = "big_pearl_1";
			}
			link.l2 = "지금은 돈이 부족하네. 미안하지만, 자네의 진주를 살 수 없겠어.";
			link.l2.go = "exit";
		break;
		
		case "big_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry52", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "가져가, 하얀 형제. 이제 네 거야.";
			link.l1 = "고마워!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// малый жемчуг
		case "small_pearl":
			dialog.text = "눈물을 몇 개나 사고 싶은가?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "small_pearl_qty";
		break;
		
		case "small_pearl_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "농담하나, 창백한 얼굴? 신들의 눈물이 필요 없단 말이지? 그럼 작별이다.";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "내가 얼마나 많은 눈물을 흘렸는지 말했지. 인디언이랑 농담하냐, 창백한 얼굴? 그럼 잘 가라.";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" 눈물이라고? 좋아. 그럼 네가 나한테 줘 "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", 백인 형제.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "여기 네 돈이다, 붉은 피부의 형제여.";
				link.l1.go = "small_pearl_1";
			}
			link.l2 = "지금은 돈이 부족해. 미안하지만, 네 진주를 살 수 없어.";
			link.l2.go = "exit";
		break;
		
		case "small_pearl_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry53", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "가져가, 하얀 형제. 이제 네 거야.";
			link.l1 = "고마워!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// золотые самородки
		case "gold":
			dialog.text = "몇 개를 사고 싶으십니까?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "gold_qty";
		break;
		
		case "gold_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "농담하냐, 창백한 놈? 쇳덩이 필요 없다 이거지? 그럼 잘 가라.";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "내가 몇 명 있는지 말했잖아. 인디언을 놀리는 거냐, 창백한 얼굴? 그럼 잘 가라.";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" 덩어리들? 글쎄, 너한테서 "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", 백인 형제여.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "여기 네 돈이 있다, 붉은 피부 형제여.";
				link.l1.go = "gold_1";
			}
			link.l2 = "지금은 돈이 부족해. 미안하지만, 네 금을 살 수 없어.";
			link.l2.go = "exit";
		break;
		
		case "gold_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry5", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "가져가라, 하얀 형제여. 이제 그것들은 네 것이야.";
			link.l1 = "고마워!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// серебряные самородки
		case "silver":
			dialog.text = "몇 개를 사고 싶으십니까?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "silver_qty";
		break;
		
		case "silver_qty":
			iQty = sti(dialogEditStrings[4]);
			npchar.quest.item.Byeqty = iQty;
			if (iQty < 1)
			{
				dialog.text = "농담하나, 창백한 얼굴? 쇳조각이 필요 없다고? 그럼 잘 가라.";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (iQty > sti(npchar.quest.item.qty))
			{
				dialog.text = "내가 몇 명 있는지 말했잖아. 인디언이랑 장난치는 거야, 창백이? 그럼 잘 가라.";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			npchar.quest.item.Summ = iQty*sti(npchar.quest.item.price);
			dialog.text = ""+iQty+" 덩어리들? 글쎄, 너한테서 "+FindRussianMoneyString(sti(npchar.quest.item.Summ))+", 백인 형제여.";
			if (sti(Pchar.money) >= sti(npchar.quest.item.Summ))
			{
				link.l1 = "여기 네 돈이다, 붉은 피부 형제여.";
				link.l1.go = "silver_1";
			}
			link.l2 = "지금은 돈이 충분하지 않아. 미안하지만, 네 은을 살 수 없어.";
			link.l2.go = "exit";
		break;
		
		case "silver_1":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.item.Summ));
			TakeNItems(pchar, "jewelry6", sti(npchar.quest.item.Byeqty));
			PlaySound("interface\important_item.wav");
			dialog.text = "가져가, 백인 형제. 이제 네 거야.";
			link.l1 = "고마워!";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		// мангароса
		case "mangarosa":
			dialog.text = "망가로사? 나도 보고 싶어.";
			link.l1 = "여기, 한번 봐...";
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			npchar.quest.mangarosa = "indian_"+(hrand(10)+1);
			dialog.text = "그래. 이것도 그 이름 중 하나야 - 망가 로사. 내가 그걸 위해 부적을 주지. 아주 좋은 부적이야, 이름도 있지 - "+XI_ConvertString(npchar.quest.mangarosa)+". 거래하나?";
			link.l1 = "이봐, 붉은 피부의 형제여, 이 식물에 대해 더 알고 싶어. 왜 그토록 이 식물이 필요한지 말해 줄 수 있겠나?";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			dialog.text = ""+npchar.name+" 이해하지 못하겠군. 거래를 원한다면 망가 로사와 아뮬렛을 교환하겠소. 그렇지 않으면 나는 가겠소.";
			link.l1 = "그래, 좋아. 거래하자.";
			link.l1.go = "mangarosa_3";
			link.l2 = "아니. 이 식물을 부적으로는 넘겨주지 않겠어.";
			link.l2.go = "exit";
		break;
		
		case "mangarosa_3":
			Log_Info("You have received an amulet");
			GiveItem2Character(pchar, npchar.quest.mangarosa);
			RemoveItems(pchar, "cannabis7", 1);
			dialog.text = "가져가 "+XI_ConvertString(npchar.quest.mangarosa)+". 쓸모가 있어.";
			link.l1 = "의심할 여지 없지. 행운을 빌어, 붉은 피부 친구야.";
			link.l1.go = "exit";
			ChangeIndianRelation(1.00);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"운명을 시험하지 마, 창백한 놈! 칼 집어넣어!","이봐, 창백한 얼굴, 무기 집어넣고 얘기나 하자. 난 문제 일으키고 싶지 않아.");
			link.l1 = LinkRandPhrase("좋아.","좋아.","말씀대로...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
