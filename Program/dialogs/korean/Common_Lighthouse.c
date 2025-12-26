#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("마을에 경보가 울렸군. 이제 나도 무기를 들어야 할 때인 것 같아...","혹시 도시 경비병들이 너를 쫓고 있지는 않나?","여기서는 피난처를 못 찾을 거다, 대신 네 갈비뼈 아래에 차가운 강철 몇 치쯤은 박힐 수 있겠지!"),LinkRandPhrase("무슨 일이야, "+GetSexPhrase("악당","놈")+"?! 경비병들이 널 쫓고 있어, 멀리 못 갈 거야, "+GetSexPhrase("더러운 해적","냄새나는 놈")+"!",""+GetSexPhrase("Filthy","Filthy")+" 살인자다! 경비병들아!!!","난 너 따위 안 무서워, "+GetSexPhrase("기어가다","냄새나는 놈")+"! 곧 우리 요새에서 교수형을 당하게 될 거다, 멀리 못 도망가..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("살고 싶은 마음이 없는 모양이군...","그런 것 같군, 이곳에는 평화로운 사람이 없는 모양이야 "+XI_ConvertString("Colony"+npchar.city+"Gen")+", 모두가 영웅이 되고 싶어 해!"),RandPhraseSimple("지옥이나 가라!","헤, 이게 네 인생의 마지막 몇 초가 되겠군..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			//belamour legendary edtion карибские нравы
			if(npchar.quest.meeting != "0" && CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "이번에는 무슨 일로 나한테 왔지?";
				link.l1 = "자네, 제라르 르크루아라는 신사를 알고 있지? 그가 나에게 보상을 남겨두었을 텐데...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("좋은 오후야, 선원! 내 이름은 "+GetFullName(npchar)+", 그리고 나는 이 등대의 관리인이오. 어떤 바람을 타고 여기까지 오셨소?","이봐! 등대에 이렇게 새로운 얼굴들이 찾아온 건 정말 오랜만이군... 내 소개를 하지 - "+GetFullName(npchar)+", 그리고 이 등대는 내 집이자 내 일터야. 무엇을 도와줄까?");
				link.l1 = "이봐, "+npchar.name+"! 내 이름은 "+GetFullName(pchar)+", 나는 배의 선장이오. 이 멋진 만을 산책하다가 이곳에 누가 사는지 궁금해서 들러 보았소.";
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "오, 내 오랜 친구여, 선장 "+GetFullName(pchar)+"! 어서 와, 어서 와! 이번엔 무슨 일로 왔나?";
				link.l1 = "이봐, 늙은 뱃사람! 여기 등대에서 혼자 쓸쓸하게 울고 있는 거 아니냐?";
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = "이제 알겠지. 나도 한때는 너처럼 선원이었어. 하지만 마지막으로 배 갑판을 밟은 지도 오래됐지. 이제는 이 등대를 내가 돌보고 있고, 물건도 좀 팔고 있어...";
			link.l1 = "그래서 정확히 뭘 팔고 있는 거지?";
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = " 이번에는 무슨 일로 왔나?";
			link.l1 = RandPhraseSimple("최근 당신네 식민지에서 무슨 흥미로운 일이 있었는지 말해줄 수 있소?","나는 한동안 뭍에 있지 않았는데... 여기 무슨 일이야?");
			link.l1.go = "rumours_lighthouse";
			link.l2 = "무엇을 팔고 있는지 보자.";
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "그래, "+npchar.name+", 내 부적이 벌써 도착했나?";
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = ""+npchar.name+", 당신에게 부적을 주문하고 싶소.";
					link.l3.go = "Trade_artefact_1";
				}
				// калеуче
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "들어봐, "+npchar.name+", 주문으로 부적을 전달하는 일을 한다는 걸 알고 있소. 그러니 부적에 대해 많이 알겠지. 이 작은 물건 좀 봐주시오 - 이게 뭔지 말해줄 수 있겠소?";
					link.l5.go = "Caleuche";
				}
				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = "이봐, 또 왔어. 그 이상한 부적들에 대해 다시 물어보려고.";
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = "당신에게 물어보려던 게 있었는데...";
			link.l4.go = "quests";
			link.l9 = "나 그냥 슬쩍 한 번 봤어...";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "가끔 나는 해안에 가서 조개를 주워. 여기서 멀지 않은 예쁜 곳이 하나 있는데, 그래서 진주가 필요하면 언제든 나한테 살 수 있지. 폭풍이 지나가면 호박도 떠내려오는데, 그것도 팔아. 다만 비싸게 받을 거야.\n가끔 파도가 난파선에서 온 온갖 신기한 물건들을 가져오기도 하고, 내 옛 친구들이 특별한 물건을 가져다주기도 해. 나는 마법 부적에 관심이 많아. 현자들은 그런 걸 비싼 돈 주고 사거든.\n특별한 경우엔 무기도 팔아. 어디서 구했냐고 묻지 마. 마을 상인은 쓸모없는 잡동사니만 사가고, 좋은 물건은 내가 직접 고치고 닦아서 직접 팔지.\n나는 럼주에 관심이 있어. 마을 선술집에서 두 페소에 한 잔씩 파는 오줌 같은 술 말고, 진짜 병에 담긴 자메이카 럼을 말하는 거야. 그건 사람을 치료하고 되살리기도 하지. 네가 가져오는 병마다 열 배로 쳐줄게. 한번 생각해 봐.";
			link.l1 = "들어봐, "+npchar.name+", 예전에 선원 친구들이 마법 부적을 가져다준다고 하셨지요. 혹시 특정 부적을 주문할 수 있을까요? 충분히 값을 치르겠습니다.";
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//иногда продает корабельные товары // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50+hrand(100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25+hrand(50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (hrand(4) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = "선장님, 최근에 많은 물자가 해안으로 떠밀려왔습니다 - "+GetGoodsNameAlt(sti(npchar.quest.goods))+". 일부는 바닷물에 망가졌지만, "+FindRussianQtyString(sti(npchar.quest.goodsqty))+" 나는 그것들을 아주 좋은 상태로 구해냈어. 좀 살래? 특별히 싸게 줄게, 바로 "+FindRussianMoneyString(sti(npchar.quest.goodsprice))+" 개당.";
				link.l1 = "아니. 최근에 모은 것들 좀 보여줘.";
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = "흠... 정직한 제안이군, 동의하지. 이걸 다시 팔면 약간의 이익은 남길 수 있겠어. 어디 보자... 그럼 총합이 "+FindRussianMoneyString(sti(npchar.quest.goodscost))+". 맞습니까?";
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = "맞아요, 선장님. 정말 좋은 거래였죠! 우리 둘 다 꽤 이득을 봤으니...";
			link.l1 = "좋아, 그럼. 선원들을 보내서 화물을 내 배로 옮기게 하겠다. 이제, 네가 팔려고 모아온 것들을 보여 줘.";
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------заказ артефактов------------------------------------------------
		case "Trade_artefact":
			if (CheckAttribute(npchar, "artefact")) // Addon-2016 Jason за дублоны
			{
				dialog.text = "글쎄, 전부는 아니지만, 어떤 장신구들은 다른 것들보다 더 자주 들어오니 내가 도와줄 수 있을 것 같군. 하지만 경고하지. 이렇게 주문하는 모든 부적은 100두블룬이 들 거야. 이해해 주길 바라...";
				link.l1 = "가격은 문제가 아니야. 어떤 부적을 내놓을 수 있지?";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "푸흣! 그 돈이면 배 한 척은 살 수 있겠군. 너무 비싸. 나 혼자서도 잘 해낼 수 있을 거야...";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "아니요, 선장님. 그런 물건은 우연히나 얻을 수 있는 거라 미리 주문하는 건 불가능합니다. 게다가, 그걸 받으려면 거의 영원만큼 기다려야 할지도 모릅니다...";
				link.l1 = "음, 그렇다면 어쩔 수 없지.";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "원하시는 대로 하십시오. 마음이 바뀌면 저를 찾아오십시오.";
			else dialog.text = "오늘 제가 판매하는 물건을 구경하시겠습니까, 선장님? 마음에 드는 게 없으시면 곧 다시 오십시오. 다른 물건이 들어올 수도 있습니다.";
			// belamour legendary edition карибские нравы -->
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				link.l1 = "이 모든 게 물론 좋지만, 내가 묻고 싶은 게 있어 – 혹시 Gerard Lecroix라는 신사를 알고 있나? 그가 나에게 보상을 남겨두었을 텐데...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			link.l1 = "아이템을 보여 줘.";
			link.l1.go = "Trade_lighthouse";
			link.l2 = "그냥 말해 봐, 네 식민지에서 요즘 무슨 흥미로운 일이 있었지?";
			link.l2.go = "rumours_lighthouse";
			link.l3 = "장사는 장사지만, 물어보고 싶은 게 있어.";
			link.l3.go = "quests";
			link.l4 = "좋은 하루 보내시오, "+npchar.name+"! 만나서 반가웠어! 다음에 또 들를게...";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "고르시오.";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "안타깝게도, 이 목록에는 지금까지 내 흥미를 끄는 것이 없어.";
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = "부두 인형인가? 화기를 좋아하나? 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 되나요?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "화약 시험관이라고? 사격 실력이야말로 어떤 접전에서도 성공의 열쇠지. 멋진데...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "의식용 칼? 넌 무거운 브로드소드로 적을 세차게 베는 걸 좋아하지? 그럼 이게 딱이야. 좋아... ";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "폴액스라고? 저렇게 거대한 도끼로 내리치면 어떤 적이든 박살나지! 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "찬차? 그건 아무리 무모한 해적이라도 겁먹게 만들겠군. 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "산호초라고? 자네 대포의 산탄이 곧장 표적에 꽂히겠군! 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 되나요?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "혹등이? 지칠 줄 모르는 게 전사의 가장 좋은 친구지. 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 되나요?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "시오테쿠틀리? 적선의 선체가 먼지로 무너지게 하라! 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "발도? 발도를 배치해 봐 – 그러면 모든 포탄이 목표에 정확히 날아갈 거야! 좋아...";
			link.l1 = "제가 주문한 것을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "카스카벨라? 뱀 독이 제일 위험하지. 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 되나요?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "응곰보 가면? 적들의 경계심을 낮춰 준다니, 하하! 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = "응곰보 방패? 총알을 피하지 못했다면, 이 부적이 네 목숨을 구해줄 수도 있지. 좋아...";
			link.l1 = "제가 주문한 물건을 언제 다시 와서 찾아가면 되나요?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "에우콜로기온? 좋은 기도는 총알도 비켜가게 할 수 있지. 좋아...";
			link.l1 = "제가 주문한 물건을 언제 다시 와서 받아가면 되나요?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "십자가인가? 이건 근접 전투에서 그리스도인에게 큰 도움이 되겠군. 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 되나요?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "엘 트로소? 이건 치명상도 그냥 긁힌 상처로 만들어 주지. 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "소그보? 그리고 대포는 항상 전투 준비가 되어 있어야지! 좋아...";
			link.l1 = "제가 주문한 물건을 언제 다시 와서 찾아가면 되나요?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "마돈나? 지극히 거룩한 성모님의 얼굴은 강력한 치유의 힘을 지니고 있지. 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 되나요?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "성수라고? 약골이라도 성수를 뿌리면 전설적인 영웅이 된다지! 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "닻이라고? 네 배가 대포 세례에도 가라앉지 않길 바라지, 하하! 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "엔콜피온? 이 부적을 지니고 있으면 네 돛은 어떤 바람도 두렵지 않을 거다. 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "기적을 행하는 자라니? 주님께서 당신의 선원들을 육지에서도 바다에서도 지켜주시길! 좋소...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "치마루타? 머리 위로 머스킷 총알이 날아가도 아무런 해도 입지 않을 거다! 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 되나요?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = "테레도? 모든 조선공이 한 번쯤은 꿈꾸는 놈이지. 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 되나요?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "소치필리? 그럼 돛을 꿰매는 데 시간이 좀 절약되겠군. 좋아...";
			link.l1 = "제가 주문한 것을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "원숭이라고? 내 생각엔 짐 나르는 노새지! 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "집시 팬이냐? 순찰대 눈이나 속여 봐라! 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "옥거북이? 그게 네가 가진 비장의 패구나! 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "몽키피스트? 그러니까 말이지 - 놈들이 널 존경하게 만들어야 해! 좋아...";
			link.l1 = "제가 주문한 물건을 언제 다시 와서 받아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "어부라고? 그건 모든 항해사의 꿈이지. 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "상인의 구슬이라고? 돈은 셈해 주는 걸 좋아하지, 안 그래? 좋아...";
			link.l1 = "제가 주문한 물건을 언제 다시 와서 찾아가면 되나요?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "에에카틀? 느리고 낡은 배라도 바람보다 더 빠르게 달릴 거야! 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "뱃사람 귀걸이? 그건 키잡이한테나 줘! 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 됩니까?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "순례자라고? 맞바람이 뒷바람으로 바뀌었군. 좋아...";
			link.l1 = "제 주문을 언제 다시 와서 찾아가면 되나요?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "두 달 뒤에, 그보다 빨리는 안 돼. 그때쯤이면 그들이 그것을 내게 가져다줄 거라 생각하네. 그러니 두 달 뒤에 돈을 가지고 기다리고 있겠네.";
			link.l1 = "좋아! 곧 갈게! 고마워, "+npchar.name+"!";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "그래, 가지고 있어. 100두블론 준비했나, 선장?"; // Addon-2016 Jason
				// belamour legendary edition -->
				if(PCharDublonsTotal() >= 100) 
				{
					link.l1 = "물론이지! 약속한 대로 여기 있어.";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "아, 돈을 배에 두고 왔네! 곧 가져올게.";
					link.l1.go = "exit";
				}
				// <-- legendary edition
			}
			else
			{
			dialog.text = "아직 아니네. 나중에 다시 찾아와. 그리고 걱정 마, 네 부적은 반드시 도착할 거야.";
			link.l1 = "좋아.";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveDublonsFromPCharTotal(100); // Addon-2016 Jason
			Log_Info("You have given 100 doubloons");
			dialog.text = "모든 게 괜찮아 보이네. 여기 네 부적이야. 행운을 빌어!";
			link.l1 = "감사합니다, "+npchar.name+"!";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("You have received "+XI_ConvertString(npchar.quest.art)+"");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "거기 뭐가 있는지 보여 줘.";
			link.l1 = "여기, 이건 고대 인디언 부적으로 보이네. 하지만 어떻게 쓰는지나 무슨 숨겨진 힘이 있는지는 전혀 모르겠어.";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "그래, 그래. 이런 걸 보여준 건 네가 세 번째야, 친구. 이 부적은 남쪽 대륙의 야생 셀바에서 가져온 거지. 파나마 근처에는 이런 장신구를 차고 다니는 인디언들이 있어. 그 붉은 피부 녀석들은 이게 자기네 ‘위대한 조상’의 유산이라고 하더군.\n그 조상들이 누구였는지, 무슨 유산을 남겼는지는 나도 모르지만, 어디서 물어보면 좋을지 조언은 해줄 수 있어. 관심 있나?";
				link.l1 = "물론이지!";
				link.l1.go = "caleuche_2";
				DelLandQuestMark(npchar);
				if (npchar.id == "BasTer_Lightman") DelMapQuestMarkShore("Mayak4");
				if (npchar.id == "Santiago_Lightman") DelMapQuestMarkShore("Mayak9");
			}
			else
			{
				dialog.text = "흠... 내가 부적을 많이 만져봤지만, 이런 건 카리브에서 처음 본다네. 미안하군, 친구야, 내가 도와줄 수 없겠어; 이런 건 나도 잘 몰라. 하지만 이게 평범한 건 아니라는 건 확실해. 다른 사람에게 물어보게. 나 같은 등대지기들 중에 부적에 대해 나만큼 아는 이들이 분명히 더 있을 걸세.";
				link.l1 = "실례합니다... 그럼 계속 질문하겠습니다.";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "도미니카에는 카리브족 마을이 있는데, 그곳 추장의 이름은 모크니테쿠브리야. 그들에겐 투투아타팍이라는 주술사가 있는데, 그는 매우 존경받는 인디언이지. 그는 카리브족은 아니고, 내가 전에 말해준 그곳 출신이야. 이 부적에 대해선 나보다 더 많은 걸 알려줄 수 있을 거야. 하지만 조심해. 투투아타팍은 백인들을 몹시 증오해. 정말로 싫어하지. 결국 예전에 그를 노예로 삼아 고향에서 끌고 갔으니까...\n";
			link.l1 = "그가 그런 식으로 카리브에 온 것이라 추정하오?";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "그래. 꽤 흥미로운 이야기지. 인디언 노예들을 태운 그 배가 마리 갈랑트 근처에서 완전히 바람이 멎어 움직이지 못했고, 갑작스러운 열병으로 선원 절반이 죽었어. 그런데 인디언들 중에는 단 한 명도 병에 걸리지 않았지!\n그 후에 선장이 미쳐서 배에 불을 질렀고, 그 틈을 타 갇혀 있던 인디언들이 폭동을 일으켜 선원들을 도륙했어. 누가 그들의 우두머리였는지 짐작할 수 있겠나?";
			link.l1 = "그래...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "그거야. 분명 주술사의 주문 때문에 바다가 시체처럼 고요해지고, 선원들에게 치명적인 병이 퍼진 거야. 이 인디언은 아주 영리하고 위험한 놈이지. 그에게 가려거든 예의를 갖추고 말조심해야 해. 그렇지 않으면 큰일 날 거야. 그리고 제물을 바치지 않으면 아예 말도 안 섞을 거다.";
			link.l1 = "그가 요구할 제물은 어떤 것일까?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "그 사람은 아무 쓸모없는 걸로는 매수할 수 없어. 내가 알기로 그는 자신의 카리브 병사들을 백인 정착지에 보내서 화기를 사 오게 하지. 그에게 선물로 머스킷총을 가져다주면, 아마도 기뻐하며 너에게 조금 관심을 줄 거야.";
			link.l1 = "감사합니다! 말씀하신 대로 하겠습니다... 그런데, 이 모든 걸 어떻게 아셨습니까?";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "내 친구는 그 불운한 배의 선원이었어. 다행히도 그 지옥에서 살아남았지... 네가 가진 것과 같은 부적을 그 친구가 차고 있는 걸 봤으니, 아마 죽은 선장도 인디언 물건을 좀 챙겼던 모양이야. 네 부적도 분명히 그 선장의 수집품 중 하나일 거야. 선장이 미쳐서 배에 불을 지르자, 선원들이 그를 죽이고 선실의 상자들을 약탈했거든.";
			link.l1 = "알겠소. 그럼 나는 도미니카에 선물을 가져가기만 하면 되겠군. 도와줘서, 그리고 흥미로운 이야기 들려줘서 고맙소!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "행운을 빌어, 친구야. 그리고 저 붉은 피부의 악마 조심해...";
			link.l1 = "...";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "그래? 투투아타파크와 얘기했지, 맞지?";
			link.l1 = "맞아. 이제 나는 부적 두 개를 더 찾고 싶어. 네가 이 유물을 보여준 사람이 내가 세 번째라고 했지. 그럼 나머지 두 명은 누구였어?";
			link.l1.go = "caleuche_10";
			DelLandQuestMark(npchar);
		break;
		
		case "caleuche_10":
			dialog.text = "한 명은 내 친구야, 투투아타파크를 카리브 제도로 데려온 그 배의 선원이었지. 그 사건 이후로 그는 어떤 배의 갑판에도 발을 디디지 않았어. 한동안 못 봤지만, 어디 사는지는 알아. 웨스트 메인, 벨리즈에서 찾아봐. 지금은 사냥꾼이 되어 정글을 돌아다니고 있거든. 이름은 퍼거스 후퍼야.";
			link.l1 = "좋아. 두 번째는?";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "두 번째 놈에 대해서는 나도 아는 게 별로 없어. 이름이 잭인지 잭슨인지, 사략선장인지, 자그마한 장사꾼인지, 아니면 그냥 모험가인지도 모르겠어. 이상한 이름의 제벡선을 가지고 있지... 흠... 그 배 이름이... 젠장, 까먹었군! 하지만 이름이 뭔가 악마 같은 거였어. 내가 그 뜻이 뭐냐고 물으니, 바다의 신들에게서 태어난 새-여자라고 하더군. 퉤! 신도 없는 놈...";
			link.l1 = "너 바보냐... 그래서 그녀 이름도 기억 못 해?";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "아니, 천둥이 나를 치라지, 나는 기억이 안 나네. 아, 그리고 그가 자기소개할 때 바베이도스 출신이라고 했어.";
			link.l1 = "이거 참! 좋아, 깃털 달린 여자들을 좋아하는 그 녀석을 다른 놈이 찾기 전에 내가 먼저 찾아볼게... 고마워, 친구. 네가 정말 큰 도움이 됐어!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "천만에, 선장님, 언제 한 번 들르세요.";
			link.l1 = "물론이지!";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
			AddLandQuestMark(characterFromId("Bridgetown_Portman"), "questmarkmain");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerType(NPChar); // belamour иначе обижается навсегда		   
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("너는 "+GetSexPhrase(" 도둑이다, 내 사랑! 경비병들아, 저 자를 잡아라"," 도둑이다! 경비병들, 저 여자 잡아라")+"!!!","이런 젠장! 잠깐 한눈판 사이에 벌써 네놈이 보물상자에 머리를 처박고 있잖아! 멈춰, 도둑놈!","경비병들! 도둑이야! 도둑을 잡아라!");
			link.l1 = "아르, 젠장!";
			link.l1.go = "fight";
		break;
		
		// belamour legendary edition карибские нравы
		case "Trial":
			dialog.text = "아, 그럼 당신이 그 선장이군! 그래, 기다리고 있었소. 제라르도 기다렸지만, 급히 어떤 원정 때문에 떠나야 해서 나에게 당신에게 대금을 전달해 달라고 부탁했소. 반드시 오라고 하더군. 여기 90 더블룬이 있소, 받아가시오.");
			link.l1 = "고마워! 정직한 사람들과 거래하니 기분이 좋군.";
			link.l1.go = "Trial_1";
		break;
		
		case "Trial_1":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 90);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.IslamonaSpaOfficer = true;
			CloseQuestHeader("Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		// <-- legendary edition
	}
}
