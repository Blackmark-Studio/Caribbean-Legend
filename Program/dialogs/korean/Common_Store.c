// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney, iQuantityGoods, iTradeGoods, iTmp;
	
	bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;
	
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	if(!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}
    
	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
	if(LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	string attrLoc   = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("마을에 경보가 울려서 모두가 자네를 찾고 있네. 내가 자네라면 거기 머무르지 않을 걸세.","도시 경비병 전원이 너를 찾으려고 온 거리를 샅샅이 뒤지고 있다네. 내가 바보인 줄 아나? 너와는 말하지 않겠어!","달려라, "+GetSexPhrase("동료","아가씨")+", 군인들이 너를 벌집으로 만들기 전에..."),LinkRandPhrase("무엇이 필요하오, "+GetSexPhrase("악당","놈")+"?! 도시 경비병들이 이미 네 냄새를 맡았으니, 멀리 못 갈 거다, "+GetSexPhrase("더러운 해적","살인마 같은 쓰레기")+"!","더러운 살인자, 당장 내 집에서 나가! 경비병들!","나는 너 따위 안 두려워, "+GetSexPhrase("기어가다","악취 나는 놈")+"! 곧 우리 요새에서 교수형을 당하게 될 거다, 멀리 못 갈 테니..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("헤, 경보 따위는 나한텐 아무 문제도 아니지...","그들이 날 절대 잡지 못할 거야."),RandPhraseSimple("닥치라고, 이 자식아, "+GetWorkTypeOfMan(npchar,"")+", 아니면 네 더러운 혀를 뽑아버릴 테니까!!","헤헷, "+GetWorkTypeOfMan(npchar,"")+", 그리고 거기 있는 모든 사람들은 해적을 잡으러 온 거야! 한마디 해주지, 친구야: 얌전히 앉아 있으면 죽지 않을 거다..."));
				link.l1.go = "fight";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("이봐, 이 자식아! 네가 원하는 건 뭐든지 가져갈 수 있다고 생각하나? 천만에! 얘들아! 무장해! 저 미친놈을 베어버려라!","뭐가 필요하면 사, 이놈아! 이제 제대로 보여주마! 얘들아, 무기 들어! 경계 태세!");
				link.l1 = RandPhraseSimple("어? 뭐라고?","어, 왜 이러는 거야?");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				//Jason --> мини-квест Дефицитный товар
				if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "유럽산 와인 한 묶음을 사고 싶소 – 한 오십에서 육십 병 정도. 재고가 충분하다고 들었소."; 
					link.l13.go = "Wine_Trader";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "다시 뵙는군요. 이 편지를 한번 봐주십시오 - 어쩌면 저에게 포도주를 파는 문제에 대해 입장을 바꿔주실지도 모르겠군요?"; 
					link.l13.go = "Wine_Repeat2";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "또 저입니다. 중단됐던 와인 거래를 다시 시작할 수 있을까요? 돈을 충분히 마련했습니다."; 
					link.l13.go = "Wine_Price";
				}
				// <-- мини-квест Дефицитный товар
				dialog.text = "무엇을 사시려는 겁니까, 나리?";
				Link.l1 = "물론이지. 상점이 뭐 하려고 있는 건데? 물건 좀 보여줘.";
				Link.l1.go = "trade_1";
				Link.l2 = "특별한 사업 목적으로 왔소...";
				Link.l2.go = "quests";
				Link.l3 = "미안하지만, 나는 가야 하오.";
				Link.l3.go = "exit";
				// туториал Мартиника
				if(NPChar.City == "FortFrance")
				{
					if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
					{
						Link.l2 = "이봐요, 나리, 일거리를 찾고 있소. 정규직이나 화물 운반 같은 건 아니고, 말하자면 심부름 같은 일이오. 혹시 도움이 필요하시오?";
						Link.l2.go = "Sharlie_storehelper";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
					{
						Link.l2 = "당신이 시킨 일을 끝냈소. 그라람 라부아를 찾았소.";
						Link.l2.go = "Sharlie_storehelper_2";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
					{
						Link.l2 = "새 조수를 만나보십시오, 나리.";
						Link.l2.go = "Sharlie_storehelper_11";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
					{
						Link.l2 = "또 저입니다, 나리. 보상을 받으러 왔습니다.";
						Link.l2.go = "Sharlie_storehelper_13";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
					{
						link.l4 = "이 귀걸이 좀 보시지요, 나리. 정글에서 죽은 산적의 시체에서 발견한 것입니다. 분명히 솜씨 좋은 보석 세공인의 작품인데, 이곳 출신은 아닌 듯합니다. 이 귀걸이에 대해 아시는 바가 있습니까?";
						link.l4.go = "Sharlie_junglejew";
					}
				}
				break;
			}			
			//<-- Бремя гасконца
			
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "선장님, 저를 구해 주셔서 감사합니다.";
				Link.l1 = "아, 천만에요.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "무슨 일입니까, 선장님? 뭔가 잃으셨습니까? 왜 제 가게 안을 그렇게 뛰어다니십니까?";
				Link.l1 = "이런, 믿기 힘들겠지만 정말이야! 그 저주받은 제라르 르크루아는 어디 있지? 나는 플로리안 쇼크가 내게 준 모든 임무를 완수했어, 상어가 나를 통째로 삼켜버려도 할 말 없을 만큼 힘들게 해냈지! 그런데 이제 보상을 받으러 왔더니, 이놈이 이미 도망가 버렸잖아!\n";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "어떻게 말해야 할지... 잃어버렸소. 내 의뢰인을 본 적 있소? 이름은 제라르 르크루아요.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "선장님, 부탁이 하나 있습니다. 도와주시겠습니까?";
				link.l1 = "무엇을 도와드릴까요?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition			
            dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("처음 뵙겠습니다, 나리! 이 땅에는 처음 오셨습니까?","어서 오십시오, 선장님! 제 상점이 나리께 봉사할 준비가 되어 있습니다.","나리, 어서 들어오십시오! 이 군도에서 살 수 있는 최고의 상품들을 기꺼이 제공해 드리겠습니다."),LinkRandPhrase("오, 선장 나리! 프랑스 식민지 전체에서 가장 훌륭한 상품들이 바로 여기, 지금, 오직 당신만을 위해 준비되어 있소!","참 반가운 만남이오, 나리! 최고의 프랑스 상품만을 취급하는 일류 상점이 당신을 위해 준비되어 있소!","전에 만난 적이 있습니까, 선장 나리? 제 가게는 본국의 최고 상점들과 견주어도 손색이 없다는 걸 아시겠지요!"),LinkRandPhrase("오! 선장 나리! 제 가게에 와 주셔서 정말 기쁩니다!","이렇게 훌륭한 카바예로를 스페인 식민지 최고의 상점에 모시게 되어 기쁩니다!","오, 고귀한 이달고 나리! 운명이 직접 나의 보잘것없는 가게로 당신을 이끌었군요! 여기서 원하시는 것은 무엇이든 찾으실 수 있습니다!"),LinkRandPhrase("안녕하십니까, 선장 나리. 여기는 처음 방문하셨습니까?","안녕하세요, 나리. 여기 처음 오셨습니까? 저희 네덜란드 상품의 품질이 분명히 기분 좋게 놀라게 해드릴 것입니다!","어서 오십시오, 선장 나리! 최고의 상품을 가장 저렴한 가격에 드립니다. 이것이 바로 네덜란드 상인의 방식이지요!"));
			Link.l1 = LinkRandPhrase("저도 만나서 반갑습니다. 제 이름은 "+GetFullName(pchar)+" 그리고 나는 이 땅에 온 지 얼마 안 되었소. 자, 군도에 있는 보물들을 보여 주시오!","저도 만나서 반갑습니다. 저는 "+GetFullName(pchar)+". ' 선장의"+pchar.ship.name+"'. 그럼, 요즘 뜨는 거래는 뭐요?",""+GetFullName(pchar)+", ' 선장"+pchar.ship.name+", 만나서 반갑소. 그래서, 나에게 무엇을 제안할 수 있겠소?");
			link.l1.go = "node_1";
			
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_store")
			{
				dialog.text = "헬렌 선장! 언제나 반갑소.";
				link.l1 = "저도 당신께 그렇듯, 감사합니다.";
				link.l1.go = "Helen_node_1";
			}
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("마을에 경보가 울려서 모두가 자네를 찾고 있네. 내가 자네라면 거기 머무르지 않을 걸세.","도시 경비병 전원이 너를 찾으려고 온 거리를 샅샅이 뒤지고 있어. 나는 바보가 아니니 너와는 말하지 않겠다!","도망쳐, "+GetSexPhrase("동료","아가씨")+", 군인들이 너를 벌집으로 만들기 전에..."),LinkRandPhrase("무엇이 필요하십니까, "+GetSexPhrase("악당","놈")+"?! 도시 경비병들이 이미 네 냄새를 맡았으니, 멀리 못 갈 거다, "+GetSexPhrase("더러운 해적","살인마 같은 쓰레기")+"!","더러운 살인자, 당장 내 집에서 나가라! 경비병!","나는 너 따위 안 두려워, "+GetSexPhrase("기어가다","악취 나는 놈")+"! 곧 우리 요새에서 교수형을 당하게 될 거다, 멀리 못 갈 테니..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("헤, 경보 따위는 나한테 아무 문제도 아니지...","놈들이 날 절대 못 잡을 거야."),RandPhraseSimple("입 다물어, "+GetWorkTypeOfMan(npchar,"")+", 아니면 네 더러운 혀를 뽑아버릴 거야!","헤헷, "+GetWorkTypeOfMan(npchar,"")+", 그리고 거기 있는 모든 사람들은 해적을 잡으러 온 자들이야! 한마디 해주지, 친구: 얌전히 앉아 있으면 죽지 않을 거다..."));
				link.l1.go = "fight";
				break;
			}
            
			//--> Jason, Сомнительное предложение
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
			{
				dialog.text = "실례하지만, 지금은 당신에게 시간을 낼 수 없습니다.";
				link.l1 = "네, 알겠습니다. 그럼 다음에 다시 들르겠습니다.";
				link.l1.go = "exit";
				break;
			}
			//<-- Сомнительное предложение
            
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "선장님, 저를 구해주셔서 감사합니다.";
				Link.l1 = "아, 천만에요.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "무슨 일입니까, 선장님? 뭔가 잃으셨습니까? 왜 제 가게 안을 그렇게 뛰어다니십니까?";
				Link.l1 = "이런, 정말 그렇다니까! 그 저주받은 제라르 르크루아는 어디 있지? 나는 플로리안 쇼크가 내게 맡긴 모든 임무를 다 완수했어, 상어가 나를 통째로 삼켜버려도 할 말 없을 만큼 정말 힘들게 해냈지! 그런데 이제 보상을 받으러 왔더니, 이 새가 이미 날아가 버렸잖아!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "어떻게 말씀드려야 할지... 잃어버렸소. 내 의뢰인을 본 적 있소? 이름은 제라르 르크루아요.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
 			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "선장님, 부탁이 하나 있소. 도와주시겠소?";
				link.l1 = "무엇을 도와드릴까요?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition           
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("오, 이게 누구신가! 뭐, 돈에는 냄새가 없다 하니 들어오시오, 선장님. 거래를 시작해 봅시다...","그대를 다시 보게 되어 기쁘다고는 할 수 없소, "+GetFullName(pchar)+"... 하지만 아직도 당신과 거래할 수 있습니다.","헤헤... 음, 집에는 초대하지 않겠소, 선장님. 하지만 내 가게는 언제든 이용하실 수 있소."),LinkRandPhrase("오, 저기 누가 왔나! 저거 혹시 "+GetFullName(pchar)+"! 거래하러 온 건가, 아니면 그냥 공짜로 가져가려는 건가? 이봐, 농담이야...","여기서 당신을 보게 되어 기쁘다고는 못 하겠군. "+GetAddress_Form(NPChar)+". 하지만 쓸 돈이 있다면, 들어오시오, 들어오시오...","거래하시겠습니까, 선장님 "+GetFullName(pchar)+"? 그렇다면, 좀 서둘러 주시겠습니까? 다른 손님들이 당신을 피하고 있어서 제 장사에 지장이 됩니다,"),LinkRandPhrase("거래하실 생각이십니까, 나리? 잠시만 기다리십시오, 현금을 세어보겠습니다 – 요즘 수상한 자들이 좀 있어서요... 물론, 선장님을 두고 하는 말은 아닙니다!","공해에서 너를 봤다면, "+GetAddress_Form(NPChar)+", 아마 돛을 더 주문했을 텐데... 하지만 여기 내 상점에서는 거래를 제안할 수 있소.","선장, 미리 말해두겠소: 천에 피가 묻었거나 커피에서 화약 냄새가 나면 받지 않겠소. 그 외에는, 한번 살펴보고 골라보시오.")),LinkRandPhrase(LinkRandPhrase("그리고 다시 만나서 반갑소, "+GetAddress_Form(NPChar)+"! 사고파는 일이든 언제나 기꺼이 도와드리겠습니다.","부탁드립니다, "+GetAddress_Form(NPChar)+", 들어오시오! 내가 가장 좋아하는 손님을 여기서 다시 보니 항상 반갑소. 이번에는 무엇을 하러 오셨소? 물건을 사러 오셨소, 아니면 팔러 오셨소?","오, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! 다시 만나서 정말 반갑습니다! 이번에는 무엇을 하시겠습니까 - 사시겠습니까, 아니면 파시겠습니까?"),LinkRandPhrase("우리 상품이 마음에 드십니까, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? 언제든지 당신을 위해 준비되어 있소 - 한번 둘러보고 골라 보시오.","안녕하세요, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". 다시 만나서 반갑습니다! 우리 상품들을 한번 구경해 보시겠습니까?","뵙게 되어 반갑습니다, 선장님! 우리 고급 상품을 알아보실 줄 알았지요. 새로 들어온 물건 한번 구경해 보시겠습니까?"),LinkRandPhrase("오, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! 어서 들어오십시오! 모든 상품이 바로 당신을 위해 준비되어 있습니다 - 이번 기회에 특별 할인이 적용됩니다!","Captain "+GetFullName(pchar)+", 또 한 번 찾아와 주셔서 저를 기쁘게 해주셨군요! 자, 마음에 드는 것을 골라 보십시오!","이번에는 무엇을 원하십니까, 선장님? 아직 저를 찾아올 줄 아신다니 기쁩니다. 필요한 모든 상품이 준비되어 있습니다 – 최고의 품질이지요!")));
			Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("이렇게 나를 맞이하는 거냐, 친구야? 좋아, 바다에서 다시 만나면 기억해두지... 떨지 마, 그냥 농담이었어. 가진 거나 보여줘.","좋아, 이 친구야. 네 물건은 필요할지 몰라도 네 입은 필요 없어. 입 다물 수 있겠어, 아니면 내가 도와줘야 하겠냐? 닥치고 물건이나 보여 줘."),RandPhraseSimple("일 얘기로 바로 들어가자, 장사꾼. 너랑 사기니 뭐니 할 기분 아니니까, 그냥 제대로 거래나 하자꾸나.","진정해, 친구. 농담은 괜찮지만, 내가 화낼 수도 있다는 걸 명심해라... 그러니 더 이상 성가시게 굴지 말고 그냥 네 물건이나 보여 줘.")),RandPhraseSimple(RandPhraseSimple("늘 당신을 찾아오는 게 즐겁지, 친구. 내 관심을 끌 만한 물건이 뭐가 있나?","늘 반갑군, 친구. 자, 몇 달째 뭍에 발도 안 디딘 바다 방랑자들에게 무슨 새 소식이 있나?"),RandPhraseSimple("그리고 또다시, 나는 ...에 있군 "+XI_ConvertString("Colony"+npchar.City+"Acc")+"! 내가 여기 없어서 다행이군. 그런데 네 창고에 나한테 남은 게 있나? 아니면 다 정리된 건가?","어떻게 안 올 수가 있겠어? 넌 항상 그보다 더 날 기쁘게 해주잖아. 자, 거기 뭐가 있나?")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase(RandPhraseSimple("전원 갑판으로 모여라! ","점검 실시하라! ")+LinkRandPhrase("무엇이 "+GetSexPhrase("신사","신사분, 아, 실례했습니다 - 숙녀분")+" 내 가게에서 필요한 행운이 있나, 헤헤?","가난한 늙은 상인에게 이런 놀라운 일이! 허허!","그래서, 어떤 순풍을 타고 내 가게까지 오셨소?"),LinkRandPhrase("항구를 열어라!","갈고리 옆으로!","곧장 앞으로 항해하라!")+RandPhraseSimple(" 여기서 찾을 수 있습니다"," 내 가게에는")+LinkRandPhrase(" 섬 전체에서 가장 좋은 가격입니다."," 훌륭한 상품 구색이오."," 최고급 품질의 상품을 준비해 두었습니다.")+RandPhraseSimple(" 저는 나리의 뜻을 따르겠습니다"," 원하는 대로 하시오")+", 선장님!"),pcharrepphrase(RandPhraseSimple("무엇을 위한 물건이오 "+GetSexPhrase("신사 여러분","신사 숙녀 여러분")+" 행운을 위해! 허허! 놈들이 해에 매달려 말라죽을 때까지!","항구에 매달린 자들이 바람에 흔들리고, 쇠사슬 소리가 실려오지. 하지만 돈에는 냄새가 없지 않은가?"),"하시겠습니까 "+LinkRandPhrase("최고급 상품을 구매하시오 "+NationNameGenitive(sti(NPChar.nation)),"화물을 사고팔기","이익 남는 화물 있나?")+RandPhraseSimple("? 무엇을 도와드릴까요!","? 제 상점이 당신을 위해 준비되어 있습니다!")+RandPhraseSimple(" 다시 만나서 반갑소"," 알아서 하시오")+", 선장님!")),NPCharRepPhrase(npchar,pcharrepphrase("내 조언을 듣고 싶다면, 선장, 산탄에는 돈을 아끼지 마시오. 죽은 자들은 훨씬 더 수색하기 쉽다는 걸 알잖소!","나는 바로 당신이 어떤 사람인지 알아챘소 "+GetSexPhrase("교활한 동료","교활한 아가씨")+". "+RandPhraseSimple("하지만 이제 보니 당신이 진짜라는 걸 알겠군 "+GetSexPhrase("영웅","무모한 자")+".","젊지만, "+RandPhraseSimple("정신을 바짝 차리고 있군.","당신은 정말 쉽게 속지 않으시겠군요."))),pcharrepphrase("나는 자네가 나포한 전리품의 모든 화물을 사들이고 싶네. 은으로 받을 텐가, 금으로 받을 텐가? 그 물건들은 언제나 값이 비싸지.","상업 항해는 수익성 좋은 사업입니다, 선장님 "+GetFullName(pchar)+", 그렇지 않소?")),NPCharRepPhrase(npchar,RandPhraseSimple("우린 놈들을 모두 주 돛에 단단히 감았지\n홋줄을 스무 번이나 돌려 묶고\n놈들을 들어 올려 시야 밖으로 던져버렸어! ",RandPhraseSimple("죽은 자의 가슴 위에 열다섯 명의 사내!","술과 악마가 나머지 놈들을 끝장냈지!")+" 요호호, 럼 한 병이다! ")+RandPhraseSimple("무슨 일이야, 선장?","무엇을 사시려는 겁니까, 선장님?"),pcharrepphrase("보아하니 흥정에 능하신 분이군요, 선장님 "+GetFullName(pchar)+". 단골손님이시니 아주 좋은 가격을 드리겠습니다!","알겠습니다, 선장님 "+GetFullName(pchar)+", 당신을 존중하여 조금 더 드릴 수 있습니다! 무엇을 원하십니까?")),NPCharRepPhrase(npchar,"맹세코, 너랑 얘기하니까 속이 뒤집힌다. "+LinkRandPhrase("땅콩 몇 개 사게. 돼지들이 그걸 아주 좋아하거든. ","여기서 누가 럼주로 네 부츠를 닦아줄 거라고 기대하나? ",pcharrepphrase("네놈 같은 부류는 잘 알지. 럼주에 취해 곧장 교수대로 가겠지.","네 어머니께서 어떻게 너를 선원으로 보내셨는지 궁금하구나! 선원이라니! 너는 재단사가 훨씬 더 잘 어울릴 텐데...")),pcharrepphrase(RandPhraseSimple("나는 그렇게 생각했어 ","그랬으면 했소 ")+RandPhraseSimple("당신이 우리 섬을 영영 떠난 줄 알았소.","다시는 당신을 볼 수 없을 거라 생각했소.")+RandPhraseSimple(" 죽은 자들이 맷돌처럼 당신 목에 매달려 있구려..."," 도대체 얼마나 많은 선원들을 산호 사이에 썩게 내버려 두었지?!"),"Captain "+GetFullName(pchar)+", 당신의 상업에 대한 열정이 내 모든 기대를 뛰어넘었소!"+RandPhraseSimple(" 출항하기 전에 마지막으로 살 물건이 있소?"," 특별히 찾는 물건이라도 있습니까?"))),"cycle",10,npchar,Dialog.CurrentNode);
			// belamour legendary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store")
			{
				if(pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik")
				{
					dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("오, 이게 누구야! 뭐, 돈에는 냄새가 없다고들 하니, 들어오시오, 선장. 거래나 해봅시다...","그대를 다시 보게 되어 기쁘다고는 할 수 없소, "+GetFullName(pchar)+"... 하지만 아직 당신과 거래할 수 있습니다.","헤헤... 음, 집에는 초대하지 않겠소, 선장. 하지만 내 가게는 여전히 당신을 위해 열려 있소."),LinkRandPhrase("오, 저기 누가 왔나! 저거 혹시 "+GetFullName(pchar)+"! 거래하러 온 거야, 아니면 그냥 공짜로 가져가려는 거야? 이봐, 농담이야...","여기서 당신을 보게 되어 기쁘다고는 할 수 없군, "+GetAddress_Form(NPChar)+". 하지만 쓸 돈이 있다면 - 들어오시오, 들어오시오...","거래하시겠습니까, 선장님 "+GetFullName(pchar)+"? 그렇다면, 좀 서둘러 주시겠습니까? 다른 손님들이 당신을 피하고 있어서 제 장사에 지장이 됩니다,"),LinkRandPhrase("거래하실 생각 있으신가요, 나리? 잠시만 기다리시오, 현금을 세어보겠소 – 요즘 수상한 자들이 좀 있어서 말이오... 물론, 선장님을 두고 하는 말은 아니오!","공해에서 너를 봤다면, "+GetAddress_Form(NPChar)+", 아마 돛을 더 주문했을 겁니다... 하지만 여기 제 상점에서는, 거래를 제안할 수 있습니다.","선장, 미리 경고하겠소: 천에 피가 묻었거나 커피에서 화약 냄새가 나면 나는 받지 않겠소. 그 외에는, 한번 살펴보고 골라보시오.")),LinkRandPhrase(LinkRandPhrase("그리고 다시 만나서 기쁩니다, "+GetAddress_Form(NPChar)+"! 사고파는 일이든 언제나 기꺼이 도와드리겠습니다.","부탁드립니다, "+GetAddress_Form(NPChar)+", 들어오시오! 내가 가장 좋아하는 손님을 여기서 다시 보게 되어 늘 기쁘오. 이번에는 무엇을 원하시오? 사러 오셨소, 아니면 팔러 오셨소?","오, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! 다시 만나서 정말 반갑습니다! 이번에는 무엇을 하시겠습니까 - 사시겠습니까, 아니면 파시겠습니까?"),LinkRandPhrase("우리 상품이 마음에 드십니까, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? 언제나 당신을 위해 준비되어 있소 - 한번 살펴보고 골라보시오.","안녕하세요, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". 다시 뵙게 되어 반갑습니다! 저희 상품들을 한번 둘러보시겠습니까?","만나서 반갑소, 선장님! 우리 고급 상품을 알아볼 줄 아실 줄 알았지요. 새로 들어온 물건들 한번 구경해 보시겠습니까?"),LinkRandPhrase("오, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! 어서 오십시오! 모든 상품이 당신을 위해 준비되어 있습니다 - 이번 기회에 특별 할인이 적용되고 있습니다!","Captain "+GetFullName(pchar)+", 또다시 찾아와 주셔서 기쁩니다! 자, 마음에 드는 것을 골라 보십시오!","이번에는 무엇을 원하십니까, 선장님? 아직도 저를 찾아오실 줄 아시니 기쁩니다. 필요한 모든 상품이 준비되어 있습니다. 최고 품질이지요!")));
					link.l14 = "듣게, 지금 곧 포르토 벨로로 떠날 참인데 자네에게서 커피와 코코아를 좀 사고 싶네. 각각 300단위씩 말일세."; 
					link.l14.go = "SharkGoldFleet";
				}
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store" && pchar.questTemp.SharkGoldFleet == "buyincar")
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("오, 이게 누구신가! 뭐, 돈에는 냄새가 없다고들 하니 들어오시오, 선장. 거래를 시작해봅시다...","그대를 다시 보게 되어 기쁘다고는 말할 수 없소, "+GetFullName(pchar)+"... 하지만 아직 당신과 거래할 수 있습니다.","헤헤... 글쎄, 내 집에는 초대하지 않겠소, 선장. 하지만 내 상점은 여전히 당신을 위해 열려 있소."),LinkRandPhrase("오, 저기 누가 있는지 좀 봐! 저거 혹시 "+GetFullName(pchar)+"! 거래하러 온 거야, 아니면 그냥 공짜로 챙기러 온 거야? 이봐, 농담이야...","여기서 당신을 보게 되어 기쁘다고는 못 하겠군, "+GetAddress_Form(NPChar)+". 하지만 쓸 돈이 있다면, 들어오시오, 들어오시오...","거래하시겠습니까, 선장님 "+GetFullName(pchar)+"? 그렇다면, 좀 서둘러 주시겠습니까? 다른 손님들이 당신을 피하고 있어서 제 장사에 지장이 됩니다,"),LinkRandPhrase("거래하실 생각이신가요, 나리? 잠시만 기다리십시오, 현금을 세어보겠습니다 – 아시다시피, 수상한 자들이 좀 돌아다니거든요... 물론, 선장님을 두고 하는 말은 아닙니다!","널 망망대해에서 봤다면, "+GetAddress_Form(NPChar)+", 아마 돛을 더 주문했을 겁니다... 하지만 여기 제 상점에서는 교역을 제안할 수 있습니다.","선장, 미리 말해두겠소: 천에 피가 묻었거나 커피에서 화약 냄새가 나면 나는 받지 않겠소. 그 외에는 한번 살펴보고 골라보시오.")),LinkRandPhrase(LinkRandPhrase("그리고 다시 뵙게 되어 기쁩니다, "+GetAddress_Form(NPChar)+"! 사고파는 일이라면 언제든 기꺼이 도와드리겠습니다.","부탁드립니다, "+GetAddress_Form(NPChar)+", 들어오시오! 내가 가장 좋아하는 손님을 여기서 다시 보니 항상 반갑소. 이번에는 무엇을 원하시오? 사러 오셨소, 아니면 팔러 오셨소?","오, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! 다시 만나서 정말 반갑습니다! 이번에는 무엇을 원하십니까? 사시겠습니까, 아니면 파시겠습니까?"),LinkRandPhrase("우리 상품이 마음에 드십니까, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? 언제나 당신을 위해 준비되어 있소이다 - 둘러보고 원하는 것을 고르시오.","안녕하세요, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". 다시 만나 뵙게 되어 반갑습니다! 저희 상품 구경해 보시겠습니까?","뵙게 되어 반갑습니다, 선장님! 우리 고급 상품을 알아보실 줄 알았지요. 새로 들어온 물건 한번 구경해 보시겠습니까?"),LinkRandPhrase("오, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! 어서 오십시오! 모든 상품이 바로 당신을 위해 준비되어 있습니다 - 이번 기회에 큰 할인도 드리니 꼭 둘러보십시오!","Captain "+GetFullName(pchar)+", 또다시 찾아와 주셔서 기쁩니다! 편하게 둘러보시고 마음에 드는 것을 골라 주십시오!","이번에는 무엇을 찾으십니까, 선장님? 아직 저를 찾아오실 줄 아시니 기쁩니다. 필요한 모든 상품이 준비되어 있습니다. 최고 품질만을 자랑하지요!")));
				link.l14 = "나는 커피와 코코아를 사러 왔소. "; 
				link.l14.go = "SharkGoldFleet_again";
			}
										
			// <-- на пару с Акулой
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("뭘 가지고 있는지 보여 줘, 이 늙은 해적아!","그저 당신의 상품을 한번 구경하고 싶었을 뿐이오, 좋은 양반."),pcharrepphrase("교수대에 맹세코, "+GetFullName(npchar)+", 날 속이게 두지 않겠소! 당장 물건을 보여 주시오!","자네 물건 좀 보자꾸나, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("그건 확실하지! 죽은 놈들은 물지 않지! 자, 네 화물칸에 뭐가 있나?","어서 본업에 집중하는 게 좋겠군, 자네. 어떤 물건들을 내게 팔 수 있나?"),pcharrepphrase("언젠가는 네가 내 전리품이 될 날이 올 거야, 헤헤. 농담이야. 물건 좀 보여 줘.","우리의 사업 이야기를 나눠봅시다, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("내가 뭘 원하냐고? 뭔가 좀 사고 싶어서 그렇지!","술을 마시다 보면 무덤에 가게 될 것이오, "+GetFullName(npchar)+". 당신의 상품을 좀 보고 싶소."),pcharrepphrase("네 할인을 잘 알지! 세 파운드 값으로 두 파운드의 카카오라니! 이제 물건이나 보여 줘.","그거야 언제나 좋은 일이죠. 그럼 흥정해 봅시다.")),"물건을 보여 줘. 말은 짧게, 일은 빠르게. 나는 급하거든.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("아, 정말 누군가를 찔러보고 싶군. 좋아, 이제 본론으로 들어가자.","다른 일로 넘어가 보세, 좋은 사람이여."),pcharrepphrase("카람바! 나는 다른 일로 여기 왔어!","특별한 사업에 대해 당신과 이야기하고 싶소, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("너와 볼 일이 있군, 늙은 해적놈!","자, 본론으로 들어가자, 친구!"),pcharrepphrase("악마를 걸고 맹세하건대, 네가 나를 속일 수는 없어, 이 악당아! 너와는 다른 볼일이 있다!","전적으로 동의합니다, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", 다른 일로 당신과 이야기하고 싶었습니다.")),NPCharRepPhrase(npchar,pcharrepphrase("벌써 짐을 다 실었나? 너와 볼 일이 있다.","나는 거래하러 온 게 아니네, 좋은 사람이여. 다른 볼일이 있소."),pcharrepphrase("그런 가격이면 벼락이나 맞으시오! 너와 거래할 일이 있다.","할인은 언제나 반갑지, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", 하지만 당신과는 다른 볼일이 있소.")),NPCharRepPhrase(npchar,pcharrepphrase("입 다물어, 이 늙은 주정뱅이야, 너랑 볼 일이 있다","럼 때문에 속이 안 좋은가 보군. 나도 자네를 딱히 좋아하는 건 아니네. 본론으로 들어가지."),pcharrepphrase("이미 한 번 등쳐 먹었잖아, 이놈아! 너랑 볼일이 있다.","당신의 빈정거림은 적절하지 않소. 나는 당신과 다른 볼일이 있소.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			/*link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("먼저 일부터 처리하고, 그다음에 즐기지. 묻고 싶은 게 있네.","지금은 아니오. 정보가 필요하오."),pcharrepphrase("네 가격은 지옥에나 처넣어! 먼저, 내가 필요한 모든 걸 다 말해.","기꺼이 도와드리겠습니다. 묻고 싶은 것이 있었소.")),NPCharRepPhrase(npchar,pcharrepphrase("충고 고맙군, 늙은 살인자. 물어볼 게 있었어.","특별히 궁금한 점이 있었소."),pcharrepphrase("금은 나중에 해도 되지. 묻고 싶은 게 있었어.","네, 동의합니다. 묻고 싶은 것이 있었소.")),NPCharRepPhrase(npchar,pcharrepphrase("내가 무슨 부탁을 하려는지 이미 알고 계시리라 믿습니다.","제 질문에 답해 주시길 바랍니다."),pcharrepphrase("가격표 말고는 생각나는 게 없나? 내가 바로 그걸 물어보려고 했거든.","그건 내 관심사가 아니야. 나는 정보가 필요해.")),NPCharRepPhrase(npchar,pcharrepphrase("너무 흥분하지 마, 이봐! 그냥 질문 하나 하려고 했을 뿐이야.","너무 흥분하지 마시오, 그러다 쓰러질라. 질문 하나만 답해 주면, 곧 떠나겠소\n"),pcharrepphrase("네가 바퀴벌레만큼이나 머리가 나쁘니 똑똑한 말을 기대하지는 않는다. 하지만 뭔가 하나쯤은 알고 있겠지.","오래 붙잡지 않겠소. 질문 하나만 하겠소.")),npchar,Dialog.CurrentNode);*/
			//link.l3 = "나는 다른 일로 왔소.";
			//link.l3.go = "quests";
			// --> Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "나는 에서 온 가격표를 가져왔소 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//<--генер почтового курьера 2 уровня	
						
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "유럽산 와인 한 묶음을 구입하고 싶소. 한 오십에서 육십 병 정도. 재고가 충분하다고 들었는데.."; 
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "다시 뵙는군요. 이 편지를 한번 봐주십시오 – 혹시 저에게 포도주를 파는 문제에 대해 생각을 바꿀 수도 있지 않겠습니까?"; 
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "또 저입니다. 중단됐던 와인 거래를 다시 시작할 수 있을까요? 돈을 충분히 마련했습니다."; 
				link.l13.go = "Wine_Price";
			}
			// <-- мини-квест Дефицитный товар
			
			// туториал Мартиника
			if(CheckAttribute(pchar, "questTemp.Sharlie.Lock") && NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
				{
					Link.l2 = "이봐요, 나리, 일거리를 좀 찾고 있소. 정규직이나 무거운 짐 나르는 일은 말고, 심부름 같은 일 말이오. 혹시 도움이 필요하시오?\n";
					Link.l2.go = "Sharlie_storehelper";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
				{
					Link.l2 = "당신이 시킨 일을 끝냈소. 그라람 라부아를 찾았소.";
					Link.l2.go = "Sharlie_storehelper_2";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
				{
					Link.l2 = "새 조수를 만나보십시오, 나리.";
					Link.l2.go = "Sharlie_storehelper_11";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
				{
					Link.l2 = "또 저입니다, 나리. 보상을 받으러 왔습니다.";
					Link.l2.go = "Sharlie_storehelper_13";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "이 귀걸이 좀 보시지요, 나리. 정글에서 죽은 산적의 시신에서 발견한 것입니다. 분명히 훌륭한 보석 세공인의 작품인데, 제 생각에는 이 근방 사람이 만든 것은 아닌 듯합니다. 이 귀걸이에 대해 아시는 바가 있습니까?";
					link.l4.go = "Sharlie_junglejew";
				}
			}
						
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "안녕하세요, 아드님의 초대로 왔습니다."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "이것은 당신의 딸에 관한 일입니다...";
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("또 보자, 늙은 주정뱅이.","좋은 하루 보내십시오, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("카람바! 어디 가지 말고 기다려, 곧 돌아올게.","여기 와 주셔서 즐거웠습니다, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! 안녕히 가십시오!")),NPCharRepPhrase(npchar,pcharrepphrase("출항하라!","잘 가시오, 좋은 사람이여."),pcharrepphrase("이봐! 거기 뭐 숨기고 있는 거야? 럼주야? 아니야? 좋아, 그럼 난 목이나 좀 축이러 간다.","죄송하지만, 시내에 급한 일이 있습니다.")),NPCharRepPhrase(npchar,pcharrepphrase("헤헤! 그럼, 또 보자!","가봐야겠소. 안녕히 계시오, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("나랑 말싸움할 생각도 하지 마라! 나 이런 데 쓸 시간 없어!","아마 내 배에서 무슨 일이 일어나고 있는지 가서 확인해야겠군. 안녕, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("무슨 일이야, 친구? 나야 - "+GetFullName(pchar)+"! 술 깨고 있어라, 내가 나중에 다시 올 테니.","자네 간이 나보다 먼저 자네를 끝장낼까 두렵군."),pcharrepphrase("네 금화랑 두블룬이나 계속 세고 있으라고, 이 늙은 여우야! 내가 다시 올 테니.","당신을 만나서 반가웠소, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;
		
		case "Helen_node_1":
			dialog.text = "무엇을 도와드릴까요? 무지개호에 물건을 채우시겠습니까, 아니면 전리품을 좀 파시겠습니까? 지금 수익성 좋은 화물에는 관심 없으실 것 같은데요, 하하.";
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("뭘 가지고 있는지 보여 줘라, 이 늙은 해적아!","그저 당신의 물건들을 한번 구경하고 싶었소, 좋은 양반."),pcharrepphrase("교수대에 맹세코, "+GetFullName(npchar)+", 날 무시하게 두지 않겠소! 당장 물건을 보여 주시오!","자네 물건 좀 보자꾸나, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("그건 확실하지! 죽은 놈들은 물지 않지! 이제, 네 창고에 뭐가 있지?","어서 본업에 집중하는 게 좋겠군, 이보게. 어떤 물건들을 내게 팔 수 있나?"),pcharrepphrase("언젠가는 네가 내 전리품이 될 날이 올 거야, 헤헤. 농담이야. 물건 좀 보여줘.","우리 사업 이야기를 나눕시다, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("내가 뭘 원하냐고? 뭔가를 사고 싶지!","술을 마시면 무덤으로 가게 될 것이오, "+GetFullName(npchar)+". 당신의 상품을 좀 보고 싶소."),pcharrepphrase("네 할인을 잘 알지! 세 파운드 값에 두 파운드 카카오라니! 이제 물건이나 보여 줘.","그거야 언제나 좋은 일이죠. 그럼 흥정해 봅시다.")),"물건 좀 보여 줘. 말은 짧게, 일은 빠르게. 난 급하거든.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("아, 정말 누군가를 찔러보고 싶군. 좋아, 이제 본론으로 들어가자.","다른 일로 넘어가 보세, 내 좋은 사내여."),pcharrepphrase("카람바! 나는 다른 일로 여기 온 거야!","특별한 사업에 대해 당신과 이야기하고 싶소, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("너와 볼일이 있다, 늙은 해적놈아!","자, 본론으로 들어가자, 친구!"),pcharrepphrase("악마에게 맹세코, 네가 나를 속일 수는 없어, 이 악당아! 너와는 다른 볼일이 있다!","전적으로 동의합니다, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", 다른 일로 당신과 상의하고 싶었습니다.")),NPCharRepPhrase(npchar,pcharrepphrase("벌써 짐을 다 실었나? 너와 볼 일이 있다.","나는 거래하러 온 게 아니네, 좋은 사람이여. 다른 볼일이 있소."),pcharrepphrase("저런 가격이면 벼락이나 맞으시오! 너와 거래할 일이 있다.","할인은 언제나 반갑지, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", 하지만 당신과는 다른 볼일이 있습니다.")),NPCharRepPhrase(npchar,pcharrepphrase("입 다물어, 이 늙은 주정뱅이야, 너랑 볼일이 있다","럼 때문에 속이 안 좋은가 보군. 나도 자네를 딱히 좋아하는 건 아니네. 이제 본론으로 들어가세."),pcharrepphrase("이미 한탕 해먹었잖아, 이 악당아! 너랑 볼일이 있다.","당신의 빈정거림은 부적절하오. 나는 당신과 다른 볼일이 있소.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("먼저 일부터 하고, 그다음에 즐기세. 묻고 싶은 게 있소.","지금은 아니오. 정보가 필요하오."),pcharrepphrase("네 놈네 값 따위는 지옥에나 처넣어! 먼저, 내가 알아야 할 모든 걸 말해.","기꺼이 도와드리겠습니다. 묻고 싶은 것이 있었소.")),NPCharRepPhrase(npchar,pcharrepphrase("조언 고맙다, 늙은 살인자. 물어볼 게 있다.","특별히 궁금한 점이 있소."),pcharrepphrase("금은 나중에 해도 되지. 물어보고 싶은 게 있었어.","네, 동의합니다. 묻고 싶은 것이 있었소.")),NPCharRepPhrase(npchar,pcharrepphrase("내가 무슨 부탁을 하려는지 이미 알고 있다고 생각하오.","제 질문에 답해 주시길 바랍니다."),pcharrepphrase("가격표 말고는 생각나는 게 없나? 내가 바로 그 얘기를 하려고 했거든.","그건 내 관심사가 아니야. 난 정보가 필요해.")),NPCharRepPhrase(npchar,pcharrepphrase("너무 들뜨지 마, 이봐! 그냥 질문 하나 하려고 했을 뿐이야.","너무 흥분하지 마시오, 그러다가는 중풍이라도 올라. 질문 하나만 답해 주면, 곧 떠나겠소."),pcharrepphrase("네가 바퀴벌레만 한 머리를 가졌으니 똑똑한 말을 할 거라 기대하지는 않아. 하지만 뭔가 하나쯤은 알고 있겠지.","오래 붙잡지 않겠소. 질문 하나만 하겠소.")),npchar,Dialog.CurrentNode);
			link.l3.go = "quests";
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("또 보자, 늙은 주정뱅이.","좋은 하루 보내십시오, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("카람바! 어디 가지 말고 기다려, 곧 돌아올게.","여기 와 주셔서 즐거웠습니다, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! 안녕히 가십시오!")),NPCharRepPhrase(npchar,pcharrepphrase("돛 올려라!","안녕히 가시오, 좋은 분."),pcharrepphrase("이봐! 거기서 뭐 숨기고 있냐? 럼이야? 아니라고? 좋아, 그럼 난 목이나 좀 축이고 오겠다.","죄송하지만, 시내에 급한 일이 있습니다.")),NPCharRepPhrase(npchar,pcharrepphrase("헤헤! 그럼, 또 보자!","가봐야겠소. 안녕히 계시오, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("나한테 말대꾸할 생각도 하지 마시오! 이럴 시간 없으니!","아마 내 배에서 무슨 일이 일어나고 있는지 가서 확인해야겠군. 안녕히 계시오, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("무슨 일이야, 친구? 나야 - "+GetFullName(pchar)+"! 술 좀 깨고 있어, 내가 나중에 다시 올게.","자네 간이 나보다 먼저 자네를 끝장낼까 두렵군."),pcharrepphrase("네 금화랑 두블룬이나 계속 세고 있으라고, 이 늙은 여우야! 내가 다시 올 테니.","당신을 만나서 반가웠소, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = "죄송하지만 지금은 너무 바쁩니다. 손님이 너무 많군요! 내일 다시 오십시오.";
				link.l1 = "아, 정말인가? 그럼, 나중에 다시 오겠네.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("나는 철환, 돛천, 약, 좋은 목재 그리고 다른 상품들도 있소! 무엇에 관심이 있소?","설탕과 향신료를 사고 싶은가? 아니면 럼주와 화약을 원하나?");
			link.l1 = pcharrepphrase(LinkRandPhrase("내 창고에 전리품이 잔뜩 있지! 돈은 냄새가 없잖아, 그렇지?","내 창고에 있는 전리품을 다 털어내고 자네 금으로 가득 채워야겠군. 하하!","오, 자네라면 무게 제대로 나가는 두블룬 한 자루에 어머니도 팔 놈이란 거 나도 알지! 하지만 난 그냥 보급품만 좀 채우려는 거야."),LinkRandPhrase("내 화물을 팔고 보급품을 보충하고 싶소.","판매할 상품을 구입하고 싶소.","대포알, 폭탄 같은 것들 좀 보여줘."));
			link.l1.go = "trade_1";

			if(CheckFunctionalTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Автозакупка товаров
			{
				link.l5 = "내 급사장이 모든 필요한 물품을 구입할 것이오...";
				link.l5.go = "TransferGoods";
			}
			
			link.l3 = pcharrepphrase(RandPhraseSimple("거래 없이 떠나겠소. 또 봅시다!","내가 가서 한잔하고 올게. 너 거기 가만히 있어!"),RandPhraseSimple("아니, 지금은 거래할 시간이 없소. 안녕히 가시오.","죄송합니다, 급히 처리해야 할 일이 있습니다. 안녕히 계십시오!"));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = "귀 기울여 듣고 있소.";
			link.l1 = "도망자를 데려왔소.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "아이고, 선장님, 정말 고맙습니다! 그 아이는 괜찮습니까? 다치진 않았나요? 그 말썽쟁이, 도망간 지 하루가 지났습니다. 내가 그 아이한테 무슨 해라도 끼칠 것처럼 보입니까? 내가 신랑감을 찾아줬습니다. 혼인도 주선했지요. 부유하고 젊은 약혼자입니다. 생김새가 썩 내세울 건 없지만, 외모 따위가 뭐가 중요합니까. 아니오! 그 아이는 항상 자기 멋대로 하려고 합니다. 저 아이 어미도 늘 그랬지, 이럴 수가!\n사실, 저 아이 어미가 옛날에 앞날 창창한 바보 녀석이랑 도망치지만 않았어도 저 아이가 태어나진 않았을 텐데... 뭐, 어쨌든... 젊음이란 건 순진하고, 어리석고, 잔인한 법이지.";
			link.l1 = "물론이오, 당신이 아버지이니 결정은 당신 몫이지만, 결혼을 서두르지는 않았으면 하오...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "네가 뭘 안다고 그래? 자식이라도 있나? 없어? 나중에 생기면 그때 얘기해라...\n그래... 그녀를 데려오는 사람에게 보상을 약속했지. 자, 받아라.";
			link.l1 = "고맙소. 그리고 그녀를 잘 지켜보시오. 내 촉으로는 저게 끝이 아닐 것 같으니.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "오, 그럼 당신이로군 "+GetSexPhrase("가져온 그 선장","가져온 그 아가씨")+" 젊은 신부를 얻은 내 방탕한 아들인가?";
				link.l1 = "그래, 내가 그들이 도망치도록 도왔지.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "오, 거기 "+GetSexPhrase("그가 우리 은인이오","그렇소, 우리 은인이오")+"보상을 기대하고 있는 거로군?";
				link.l1 = "글쎄, 보상은 없어도 괜찮지만, 당신의 감사 인사만으로도 충분하오.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "제 아이가 궁지에 몰렸을 때 버리지 않고, 난처한 상황에서 벗어날 수 있도록 도와주신 데 대해 진심으로 감사드립니다. 감사의 뜻을 전하고 싶사오니, 이 보잘것없는 금액과 제 선물을 부디 받아주십시오.";
			link.l1 = "감사합니다. 이 젊은 부부를 도울 수 있어 기뻤습니다.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "감사하다고? 무슨 감사?! 저 멍청이는 반년 동안 일도 안 하고 빈둥거리기만 했어. 그런데 연애할 시간은 또 있지! 내가 저 나이였을 땐 이미 내 사업을 하고 있었단 말이다! 푸흣! 총독에게는 혼기가 찬 딸도 있는데, 저 얼간이는 혈육도 없는 계집애를 내 집에 데려와서는 감히 내 축복을 바란다고?!";
			link.l1 = "흠... 진심을 믿지 않는 모양이군?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "무슨 감정? 어떤 감정을 말하는 거요? 감정이라니... 그 나이에 어찌 그렇게 생각이 없을 수 있단 말이오?! 젊은 것들의 변덕을 받아주고, 중매쟁이 노릇까지 하다니 부끄러운 줄 아시오! 집에서 소녀를 데려간 것뿐 아니라, 내 풋내기의 인생까지 망쳐 놓았소. 당신에게 고마움 따윈 없을 것이오. 이만 작별이오.";
			link.l1 = "알겠소, 당신도 마찬가지요...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		// Warship. Автозакупка товаров -->
		case "TransferGoods":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = LinkRandPhrase("...이미 끝났소. 이제 어느 배에 실을지 결정만 남았군.","당신네 재무관이 이미 그 일을 끝냈소. 이제 어느 배에 짐을 실을지 결정합시다.","예, "+PChar.name+", 알고 있소. 이미 나를 찾아왔지. 이제 어느 배에 짐을 실을까?");
					
				for(i=0; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						if(!GetRemovable(chref)) continue;
						
						attrL = "l"+i;
						Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
						Link.(attrL).go = "TransferGoodsTo_" + chref.id;
					}
				}
				
				Link.l99 = "생각이 바뀌었소, 더 이상 필요한 것은 없소.";
				Link.l99.go = "exit";
			}
			else // Корабля нету
			{
				dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("장난하는 거야? 네 배는 어디 있지? 부두에 안 보이는데!","악마에게 맹세코, 너한테 속지 않을 거야! 네 배는 부두에 없잖아!"),pcharrepphrase("항구에 당신 배가 보이지 않소, 선장 "+GetFullName(pchar)+". 혹시 그녀가 '플라잉 더치맨'은 아니겠지?","선장님, 부두에서 화물을 싣는 게 훨씬 쉽습니다. 저도 그 방법을 선호하지요. 배를 빨리 가져오시고 다시 오십시오."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"귀찮게 하네! 좋아, 이 늙은 여우야, 곧 보자!","당신을 속이고 싶지 않았소, "+GetFullName(npchar)+", 섬 반대편에 배가 있어."),pcharrepphrase("아니오. 내 배 이름은 '블랙 펄'이오. 왜 그렇게 창백해졌소? 하하! 농담이오!","조언해 줘서 고마워, 꼭 참고할게."));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // Тут уже не проверяем, есть корабль или нету (выбрали корабль, в который груз не помещается)
			dialog.text = LinkRandPhrase("그래서, 선장님, 어느 배에 짐을 실을까요?","그래서, 어느 배에 짐을 실어야 하오?",PChar.name+", 어느 배의 창고에 물건을 실어야 하오?");
				
			for(i=0; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if(cn > 0)
				{
					chref = GetCharacter(cn);
					if(!GetRemovable(chref)) continue; // Если квестовый - пропускаем
					
					attrL = "l"+i;
					Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}
			
			Link.l99 = "마음이 바뀌었소, 아무것도 필요하지 않소.";
			Link.l99.go = "exit";
			break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase("모든 준비가 끝났소! 선택한 배의 선적이 시작되었소.","좋소, 선택한 배에 화물을 싣기 시작했소.","선장님, 선택하신 배에 화물을 싣기 시작했습니다.");
					link.l1 = "감사합니다. 거래하게 되어 기쁩니다.";
					link.l1.go = "exit";
          SetPriceListByStoreMan(rColony); // mitrokosta обновляем список цен
					WaitDate("", 0, 0, 0, 1, 0); // Крутим время
				}
				else
				{
					dialog.text = LinkRandPhrase("선장님, 재무관이 요청한 모든 물품이 이미 말씀하신 배에 실려 있습니다!","선장님, 말씀하신 배에 모든 물품을 이미 실었습니다!","선장님, 그 배는 이미 모든 물자가 실려 있어서 정비가 필요 없습니다.");
					link.l1 = "그래, 맞아.";
					link.l1.go = "exit";
					link.l2 = "그럼 다른 배를 골라야겠군.";
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("유감이지만, 그 종류의 배로는 그렇게 많이 실을 수 없습니다.","선장님, 당신 배에는 그만한 화물을 실을 수 없어요!","선장님, 배의 창고에 그만한 화물을 실을 수 없습니다!");
				link.l1 = "그래, 네 말이 맞아. 다른 배를 골라야겠어.";
				link.l1.go = "TransferGoods_2";
				link.l2 = "생각해 봤는데... 아무것도 살 필요 없겠군.";
				link.l2.go = "exit";
			}
			break;
		// <-- Автозакупка товаров

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("장난하는 거야? 네 배는 어디 있지? 부두에 안 보이는데!","악마에게 맹세코, 너한테 속지 않아! 네 배는 부두에 없잖아!"),pcharrepphrase("항구에 당신 배가 보이지 않는데요, 선장님 "+GetFullName(pchar)+". 설마 그녀가 '플라잉 더치맨'은 아니겠지?","선장님, 부두에서 화물을 싣는 게 훨씬 쉽습니다. 배를 빨리 가져오고 다시 오십시오."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"귀찮게 하네! 좋아, 이 늙은 여우야, 곧 보자고!","당신을 속이고 싶지 않았소, "+GetFullName(npchar)+", 섬 반대편에 배가 있어."),pcharrepphrase("아니오. 내 배 이름은 '블랙 펄'이오. 왜 그렇게 창백해졌소? 하하! 농담이오!","조언 고맙소, 그들이 잘 활용할 것이오."));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "임대료는 아직도 나에게 빚지고 있소\n "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "좋아, 지금 임대료를 내겠소.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "나중에 다시 오겠소.";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "오라.";
				link.l1 = "고맙소.";
				link.l1.go = "storage_2";
			}
			link.l2 = "아니, 마음이 바뀌었소.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "그래, 항구에 내 창고가 하나 있지 - 화물 5만 센트너까지 보관할 수 있어. For "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+" 한 달마다 당신의 물품을 안전하게 보관해 드릴 수 있습니다. "+"이 일에는 경비, 침수 방지, 그리고 쥐 처리까지 포함되어 있소. 어떻게 하시겠소? 그리고... 한 달치 선불도 필요하오.";	
			link.l1 = "정장이라. 내가 좀 봐도 되겠소? 거기 쥐가 많소?";
			link.l1.go = "storage_1";
			link.l2 = "아니, 그냥 물어보는 거야. 필요할 때 쓸 수 있으니까...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "말했듯이, 한 달 치 선불이 필요하오. 그리고 쥐는 절대 안 되오!";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "당신은... 정말 장사꾼 기질이 있군요. 여기 돈이오 - 이 창고를 빌리겠소.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "당신은... 정말 장사꾼 기질이 대단하군요. 알겠소, 곧 돈을 가지고 돌아오겠소.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "벌써 떠나시나요? 아쉽군요 - 정말 조건이 훌륭한 곳입니다. 제가 장담하건대, 카리브 해 어디에서도 이런 거래는 찾기 힘드실 겁니다.";
			link.l1 = "나는 면죄해 달라고 했소. 아니면 내가 공기 저장에 돈을 내야 한다는 말이오? 다른 임차인을 찾아보시오.";
			link.l1.go = "storage_4";
			link.l2 = "카리브 해 어디에도 없다고? 알겠소, 그럼 당분간은 이 얘기 그만두겠소.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "그리고 임대료는 아직도 나에게 빚지고 있소\n "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "좋소.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "물건을 챙기시오, 내가 창고를 닫겠소.";
				link.l1 = "좋소.";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		case "business":
			iTest = 0;			
	
	
			//Jason --> генератор Сомнительное предложение
			/*if (hrand(3) == 1 && !CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && !CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && sti(npchar.nation) != PIRATE && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0) 
			{
				if (!CheckAttribute(npchar, "Contraoffer") || GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) 
				{
					dialog.text = "오! 마침 잘 오셨습니다, 선장님. 부탁 하나 드리고 싶습니다.";
					link.l1 = "들어보자."; 
					link.l1.go = "Contraoffer";
					break;
				}
			}
		
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store") 
			{
				dialog.text = "듣고 있소, 선장.";
				link.l5 = "주문하신 물건을 가져왔소."; 
				link.l5.go = "Contraoffer_check";
			}
			
			if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //единичный вариант за всю игру, ака 'пасхалка'
			{
				dialog.text = "오! 딱 맞춰 오셨군요, 선장님. 특별한 부탁이 있소.";
				link.l5 = "들어보자."; 
				link.l5.go = "Contraoffer_slaves";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store") 
			{
				dialog.text = "듣고 있소, 선장.";
				link.l5 = "노예들을 데려왔소."; 
				link.l5.go = "Contraoffer_slaves_check";
			}*/
			// <-- генератор Сомнительное предложение
	
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "이봐, 자네는 온갖 물건을 다루지... 어제나 오늘, 누가 자네에게 팔겠다고 한 물건이 있나\n "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l16.go = "Device_Trader";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			// belamour legendary edition втречается чаще
			if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && hrand(2) == 2 && !CheckAttribute(pchar, "questTemp.Shadowtrader_Block")) 
			{
				dialog.text = "선장님, 부탁드릴 일이 있습니다. 승낙해 주신다면 충분한 보수를 드리겠습니다.";
				link.l1 = "흥미롭군. 그래서, 무슨 문제가 있나?"; 
				link.l1.go = "Sunplace_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "선장님, 다시 뵙게 되어 기쁩니다. 이미 제 부탁을 들어주셨다는 것도 알고 있습니다. "+pchar.GenQuest.Sunplace.Trader.Enemyname+".";
				link.l1 = "헤! 그건 확실하지. "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Name")))+" "+pchar.GenQuest.Sunplace.Trader.ShipName+" 그리고 화물은 - "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+", 이제 더 이상 당신의 경쟁자 소유가 아니오."; 
				link.l1.go = "Sunplace_complete";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "나리, 선장님... 왜 그를 죽이셨습니까? 나는 그저 그의 배만 침몰시켜 달라고 부탁했을 뿐이오! 성모 마리아여, 이제 내 손에 죄 없는 이의 피가 묻었구려...";
				link.l1 = "헤이! 왜 그러는 거야, "+npchar.name+"? 그게 뭐가 중요하겠소 – 이제 더는 당신을 괴롭히지 않을 테니, 그게 중요한 거요!"; 
				link.l1.go = "Sunplace_complete_murder";
				break;
			}
			// <-- генератор Место под солнцем
			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "일거리가 있었는데\n "+GetFullName(&Characters[iTmp])+" 이미 저를 위해 그 일을 맡았소.";
				link.l1 = "정말인가? 그럼, 나중에 다시 오겠소.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"무슨 일이오?! 전부 말해 보시오!","듣고 있소. 무슨 거래를 말하는 거요?");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )
    				{
    					link.l1 = RandPhraseSimple("내 배의 선창에 당신 상점으로 가져온 물건이 한 묶음 있습니다.","내 배가 당신 가게로 물품을 운송하라는 임무를 받았소. 화물은 지금 하역 중이오.");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "유감스럽게도, 나는 내 약속을 지킬 수 없게 되었소. 정치적 상황 때문에 물품을 전달할 수 없소.";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("화물 운송을 위해 내 배를 전세로 내줄 수 있소.","나는 훌륭한 배를 가지고 있소, 어디든 필요한 곳에 어떤 화물이든 운송할 수 있소.");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "배를 전세 내시겠습니까, "+GetAddress_FormToNPC(NPChar)+"? 나는 믿을 만한 배와 경험 많은 선원을 거느리고 있소.";
    				link.l1.go = "generate_quest";
    			}
				link.l22 = "나는 다른 일로 왔소.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("아, 바다에서 정말 지쳐버렸어... 그런데 말이지, 친구야, 지금 나한테 돈이 진짜 문제야.","좋아, 늙은 여우야, 우리 재정 문제에 대해 이야기해 보자."),RandPhraseSimple("재정 문제에 대해 당신과 상의하고 싶습니다.","재정 문제에 대해 논의합시다, 이 이야기는 꼭 해야 하니까요."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple("나는 한 사람의 부탁을 받고 여기 왔소. 그의 이름은 총독이오 "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" 저를 당신에게 보냈습니다. 뭔가를 받아가라고 해서요...");
					link.l4.go = "IntelligenceForAll";
				}	
				
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("최신 소문 좀 들려줄 수 있겠어? 어차피 하루 종일 여기서 빈둥거리잖아.","호들갑 떨지 마, 이 늙은 사기꾼아. 육지에선 무슨 새 소식이 있지?"),RandPhraseSimple("바다에서 영원을 보낸 기분이군. 이 지역에는 무슨 새로운 소식이 있나?","최신 소식은 다 알고 있겠지? 무슨 중요한 일이 있었나?"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage") && Pchar.location.from_sea == "Pirates_town")
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "창고로 데려가시오. 상태가 어떤지 직접 보고 싶소.";
						link.l7.go = "storage_0";
						link.l8 = "창고를 내놓기로 했소. 이제는 필요 없으니.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "실례하오, 이보게 좋은 양반 - 혹시 창고를 임대하고 있지 않소?";
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <-- ugeen
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "보시다시피, 제 동료를 찾으려고 하고 있습니다, "+pchar.GenQuest.FindFugitive.Name+" 그가 이름이오. 포트 로얄에서 선술집 사람들에게 들으니 그가 당신네 정착지로 향했다고 하더군요. 혹시 그를 만난 적 있소?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
				
				// <-- homo
				link.l99 = "하지만 지금은 이야기할 시간이 없소.";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"섬 반대편에 배를 두고 왔어. 나중에 다시 올게!","실례합니다, "+GetFullName(npchar)+", 나중에 오겠소. 내 배가 아직 부두에 도착하지 않았으니."),pcharrepphrase("제길! 이 멍청이들이 선적 준비도 안 해 놨잖아! 나중에 다시 오겠다!","실례하오, 내 배를 부두에 정박시키라고 명령을 내려야 하오!"));
                link.l1.go = "exit";
				link.l22 = "나는 다른 일로 왔소.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("아, 바다에서 정말 지쳐 버렸지... 그런데 말이야, 친구, 지금은 돈이 정말 문제야.","좋아, 늙은 여우야, 우리 재정 문제에 대해 이야기해 보자."),RandPhraseSimple("당신과 재정 문제에 대해 상의하고 싶습니다.","우리가 논의해야 할 재정 문제에 대해 이야기합시다."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple("나는 한 사람의 부탁을 받고 여기 왔소. 그의 이름은 총독이오 "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" 당신에게 저를 보냈습니다. 뭔가를 받아가라고 했는데요...");
					link.l7.go = "IntelligenceForAll";
				}
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "보시다시피, 제 동료를 찾으려고 하고 있습니다, "+pchar.GenQuest.FindFugitive.Name+" 그가 이름이오. 포트 로얄의 선술집에서 사람들이 그가 당신네 정착지로 향했다고 하더군요.\n혹시 그를 만난 적 있으시오?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//проверка враждебности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "아니, 네 서비스는 필요 없어! 적어도 네가 아직 \n 적들과 함께 있는 한은 말이야 "+NationNameAblative(sti(NPChar.nation))+".";
					link.l1 = "그렇다면, 안녕히 가십시오.";
					link.l1.go = "exit";
				}
				else
				{
                    // проверка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear()+"그대는 "+GetFullName(pchar)+", 아니오? 사람들이 그러던데\n "+RandPhraseSimple("당신에 대해 무서운 이야기들이 많아요","너에 대해 안 좋은 소문이 많아")+", 그리고 나는 너와는 거래하고 싶지 않아.";
						link.l1 = RandPhraseSimple("물론이지 - 한 번만 실수해도 모두가 기꺼이 너를 깔보고 침 뱉으려 하지.",RandSwear()+"음, 바다에서는 더 할 만한 일이 있지, "+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // проверка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar,"헤헷, "+GetAddress_Form(NPChar)+", 오늘은 화물 일에 쓸 시간이 없소. 내일 다시 오시오.","내일 다시 오시오. 어쩌면 유리한 제안을 할 수도 있소.");
						link.l1 = "알겠소, 내일 다시 오겠소.";
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //проверяем импорт/экспорт
							iTradeGoods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); //Jason
    						//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
    						RecalculateSquadronCargoLoad(pchar); // fix неверное место
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
							if (sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units)*sti(iQuantityGoods) > 1500) iQuantityGoods = makeint(1500/(sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units))); //Jason: больше 1500 массы не дадим - большие фрахты только через ПУ
    						if (iQuantityGoods < 100)// это в шт. товара
    						{
    							dialog.text = NPCharRepPhrase(npchar,"네 초라한 낡은 배로는 전부 실을 수 없으니, 오늘은 거래가 없겠군.","유감스럽게도, 선장님 "+GetFullName(pchar)+", 내 배달을 위해 더 큰 배가 필요하겠군.");
    							link.l1 = NPCharRepPhrase(npchar,"내 배도 나쁘진 않지만, 네 말도 일리가 있군. 안녕.","무슨 말씀인지 알겠소, 사업은 사업이지. 안녕히 가시오.");
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
    							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							pchar.CargoQuest.iDaysExpired = 25 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = ", which is on " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Voc");
                                }
                                dialog.text = "오! 마침 당신에게 부탁을 하려던 참이었소. 있잖소, 내가 화물을 전달해야 하는데\n "+GetGoodsNameAlt(iTradeGoods)+" 총 "+FindRussianQtyString(iQuantityGoods)+" 마을로 "+sNation+sTemp+", 그리고 빠르면 빠를수록 좋소. 만약 그때까지 해낸다면 "+FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired))+", 그러면 도착하자마자 받을 수 있습니다 "+FindRussianMoneyString(iMoney)+" 보상으로 드리겠소. 어떻소?";
    							link.l1 = "나도 동의하는 것 같소.";
    							link.l1.go = "exit_trade";
    							link.l2 = "이건 아마 내 일이 아닌 것 같군.";
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = "군도 내의 정치적 현실 때문에 내가 거래를 할 수 없소. "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"사냥꾼")+" 모두에게 적대적이라 나만 가게에 남겨두고 떠났어.";
    						link.l1 = "오! 미안하오. 행운을 빌겠소.";
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar,"꺼져라, 쓸데없는 잡담할 시간 없다!","이미 당신에게 줄 것이 없다고 말했소.");
				link.l1 = NPCharRepPhrase(npchar,"예의를 지켜라, 아니면 내가 예절이 뭔지 가르쳐 주겠다!","아, 미안합니다!");
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear()+"그 거래를 너무 늦게 기억한 것 같지 않소? 내가 물건을 다시 주문해야 했소. 안녕히 가시오.";
				link.l1 = "용서해 주시오, 급히 일이 있었소. 내가 손해를 보상하면 내 평판이 회복될 수 있을까?";
				link.l1.go = "generate_quest_failed";
				link.l9 = "행운을 빕니다.";
				link.l9.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = "정말이오! 꽤 오래 기다렸소. 내게 화물을 가져다줘야 하오\n "+GetGoodsNameAlt(iTradeGoods)+" 총 "+FindRussianQtyString(iQuantityGoods)+" 그리고 그것을 받고 "+FindRussianMoneyString(sti(pchar.CargoQuest.iMoney))+".";
				link.l1 = "정확히 그렇소.";
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear()+"사과드려야겠소, "+GetAddress_Form(NPChar)+".  문제는 내가 있었다는 것이오 "+RandPhraseSimple("곤란한 상황이라 당신에게 돈을 지불할 수 없겠소"," 이미 그 화물은 다른 상인에게서 더 좋은 값에 샀소")+". 선박 임차료로, 당신이 운송하던 모든 화물을 가져가시길 제안합니다.";
				link.l1 = RandSwear()+RandPhraseSimple("그리고 나는 그 빌어먹을 화물을 모든 위험에서 지켜 왔어! 그 때문에 쥐만 이백 마리나 잡았다고!","나를 궁지에 몰아넣었으니, 동의할 수밖에 없군.");
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = "그게 전부가 아니오! 우리 거래에 따르면, 나는 필요하오\n "+FindRussianQtyString(iTmp)+" 개 더.";
				link.l9 = RandPhraseSimple("예, 그렇습니다. 그럼 부족분은 내가 메워야겠군요. 이따 봅시다.",RandSwear()+"이 저주받은 쥐들이 화물을 망쳐 놓았군. 부족분은 내가 메우고 돌아오겠소.");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = "훌륭하군! 여기 보상이오, 선장 "+GetFullName(pchar)+".";
				link.l1 = "당신과 함께 일해서 즐거웠습니다.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "좋아... 총액은 "+FindRussianMoneyString(iMoney)+" 우리 거래 조건 위반으로 인한 손해만 보상될 것이오.";
			link.l1 = "이런 젠장! 안 돼, 그건 못 하겠어! 다시는 화물을 운송하지 않겠다! 바다엔 그런 잡동사니가 이미 넘쳐나니까!";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "여기 필요한 금액이오";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "훌륭하군. 이제 동료들에게 당신과 거래하는 것이 아직 합리적이라고 말할 수 있겠소.";
			link.l1 = "감사합니다! 다시는 실망시키지 않겠습니다.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = "흠. 이전 계약에서 약속한 의무를 이행하지 않았다고 들었소. 그런데 또 다른 계약을 원한다니? 당신은 화물을 전달하기로 했었지\n "+GetGoodsNameSeaSection(&Goods[iTradeGoods])+" 에게 "+XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony)+".";
			link.l1 = "그래, 맞아! 네 말이 옳아!";
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear()+GetAddress_Form(NPChar)+", 나를 실망시키는군!!! 이 문제를 해결할 방법이 있지 않겠소?";
			link.l1 = "알겠소. 화물을 반드시 전달하도록 최선을 다하겠소.";
			link.l1.go = "exit";
			link.l2 = "아니요, 할 수 없습니다. 미안합니다";
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "잠깐! 당신 배에 물자가 충분하지 않소! 당신에게는 없소\n "+FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar,iTradeGoods))+" 화물 단위입니다.";
				link.l9 = RandPhraseSimple("예, 그렇군요. 그럼 부족분을 내가 메워야겠군요.",RandSwear()+"쥐들이 화물을 망쳐 놓았소. 부족한 양은 내가 사서 돌아오겠소.");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "알겠소, 알겠소... 내가 그 화물을 다시 가져가겠소.";
    			link.l1 = "감사합니다! 다시는 실망시키지 않겠습니다!";
    			link.l1.go = "exit";
    			ChangeCharacterComplexReputation(pchar,"nobility", -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;
	
//Jason --> мини-квест Дефицитный товар
		case "Wine_Trader":
			dialog.text = "무슨 말을 하는 거요? 분명히 오해하신 겁니다 - 나는 유럽산 와인을 그렇게 대량으로 거래한 적이 없소. 한두 병 정도, 그 이상은 아니오. 하지만 이 지방 와인은 얘기가 다르지요 - 그건 넉넉히 가지고 있고, 병 단위가 아니라 데미존 단위로 팝니다!\n";
			link.l1 = "제기랄! 하지만 들은 말이...";
			link.l1.go = "Wine_Trader_1";
		break;
		
		case "Wine_Trader_1":
			dialog.text = "무슨 말을 들었는지 모르겠지만, 다시 말하겠소. 내 창고에는 유럽산 와인이 없소. 이 일에 대해 내가 할 말은 이것뿐이오.";
			link.l1 = "좋아... 그럼 내가 가서 정리하고 오지, 그럼!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "5");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			DeleteAttribute(pchar, "questTemp.Wine.Trader");
			pchar.questTemp.Wine.Repeat1 = "true";
		break;
		
		case "Wine_Repeat2":
			RemoveItems(PChar, "letter_1", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "그건 또 다른 이야기군. 여기엔 별별 사람들이 와서 쓸데없는 질문을 하거든. 자, 그럼 흥정을 해볼까?";
			link.l1 = "물론이지!";
			link.l1.go = "Wine_Price";
			pchar.questTemp.Wine.wait = "true";
			DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
			SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId(pchar.questTemp.Wine.ItemTraderID), "questmarkmain");
		break;
		
		case "Wine_Price":
			dialog.text = "몇 병이 필요하십니까? 한 병 가격은 500페소이며, 최소 주문 수량은 20병입니다.";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Wine_Qty";
			link.l2 = "지금은 돈이 부족하군. 나중에 다시 오겠소.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Wine.Qty = sti(iQty);
			if (iQty < 20)
			{
				dialog.text = "나는 잡상인이 아니오, 선장. 내 기억으로는, 자네가 더 큰 물량에 대해 이야기하지 않았던가?";
				link.l1 = "죄송합니다... 그럼 금액을 다시 생각해 봅시다.";
				link.l1.go = "Wine_Price";
				break;
			}
			if (iQty > 70)
			{
				dialog.text = "유감스럽게도, 그만한 돈은 없습니다.";
				link.l1 = "안타깝군... 그럼 금액을 다시 생각해 보지.";
				link.l1.go = "Wine_Price";
				break;
			}
			pchar.questTemp.Wine.Summ = sti(iQty)*500;
			dialog.text = ""+sti(iQty)+" 병 말인가? 좋아. 그건 돈이 들지. "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ))".";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
			{
				link.l1 = "여기 있습니다.";
				link.l1.go = "Wine_Qty_1";
			}
			link.l2 = "지금은 돈이 부족하오. 나중에 다시 오겠소.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty_exit":
			dialog.text = "괜찮소, 하지만 너무 오래 걸리진 마시오. 이 물건들은 여기서 꽤 인기가 많으니.";
			link.l1 = "곧 돌아올게!";
			link.l1.go = "exit";
		break;
		
		case "Wine_Qty_1":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
			dialog.text = "자, 보자... 모든 게 이상 없어 보이오. 물건을 가져가시오.";
			link.l1 = "감사합니다! 행운을 빕니다!";
			link.l1.go = "Wine_Qty_2";
		break;
		
		case "Wine_Qty_2":
			pchar.quest.Wine_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.wait");
			TakeNItems(pchar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			PlaySound("interface\important_item.wav");
			Log_Info ("You have received wine");
			AddQuestRecord("Wine", "8");
			DelLandQuestMark(npchar);
			DialogExit();
		break;
		// <-- мини-квест Дефицитный товар
		
// Jason --> -------------------------генератор Сомнительное предложение----------------------------------------
		int iCGood, amount;
		case "Contraoffer":
			pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			while (sti(pchar.GenQuest.Contraoffer.Trader.Goods) == -1)
			{
				pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			}
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.Qty = makeint(15*(sti(pchar.rank)+30)/(sti(Goods[iCGood].Weight)/sti(Goods[iCGood].Units))*(8-sti(RealShips[sti(pchar.ship.type)].Class)));//количество
			pchar.GenQuest.Contraoffer.Trader.Price = sti(Goods[iCGood].Cost)/sti(Goods[iCGood].Units)*3;//цена единицы товара
			pchar.GenQuest.Contraoffer.Trader.Summ = sti(pchar.GenQuest.Contraoffer.Trader.Price)*sti(pchar.GenQuest.Contraoffer.Trader.Qty);//сумма
			pchar.GenQuest.Contraoffer.Trader.Days = 30+hrand(20);//срок
			pchar.GenQuest.Contraoffer.Trader.Chance = rand(5);//17% вероятности, что патруль накроет
			dialog.text = "좋은 거래를 하려고 했지만, 그를 위해 아직 특정 물건이 더 필요하오 - "+GetGoodsNameAlt(iCGood)+". 문제는 이 물품이 우리 식민지에서는 밀수품이라서, 무역 선장들에게서 구입할 수 없다는 점이오\n내게 필요한 것은 "+FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty))+" 그 물건 몇 단위를 나에게 가져다줄 수 있겠소? 보수를 넉넉히 드리겠소, "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price))+" 개당, 그래서 합계는 "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+". 아, 그리고 그건 반드시 그때까지 필요하오 "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days))+". 그래서, 도와주실 건가요?";
			link.l1 = "흠... 흥미롭군. 동의하지!";
			link.l1.go = "Contraoffer_1";
			link.l2 = "밀수품 운반이라니? 미안하지만, 관심 없어.";
			link.l2.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;
		
		case "Contraoffer_1":
			dialog.text = "훌륭하군. 동의해 주어서 기쁘네. 그러면, 물건을 가지고 돌아오기를 기다리겠네.";
			link.l1 = "곧 돌아오겠소!";
			link.l1.go = "exit";
			rColony = GetColonyByIndex(FindColony(npchar.city));
			SetNull2StoreGood(rColony, sti(pchar.GenQuest.Contraoffer.Trader.Goods));//нулим товар
			pchar.GenQuest.Contraoffer = "begin";
			pchar.GenQuest.Contraoffer.Trader = "true";
			pchar.GenQuest.Contraoffer.Trader.City = npchar.city;
			pchar.GenQuest.Contraoffer.Trader.Nation = npchar.nation;
			iCGood = pchar.GenQuest.Contraoffer.Trader.Goods;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "1");
			AddQuestUserData("Contraoffer", "sGoods", GetGoodsNameAlt(iCGood));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Trader.City+"Gen"));
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Trader.Days), false);
		break;
		
		case "Contraoffer_check":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			amount = sti(pchar.GenQuest.Contraoffer.Trader.Qty) - GetSquadronGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods));
			if (amount > 0)
			{
				dialog.text = "농담하는 건가? 내가 필요한 물건이 전부 있지 않잖아!";
				link.l1 = "죄송합니다, 제 실수였습니다...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "그럼 어디 보자. 당신이 가져오기로 한 화물은 "+GetGoodsNameAlt(iCGood)+" 총 "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty)+". 맞습니까?";
				link.l1 = "그렇소, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_pay";
			}
		break;
		
		case "Contraoffer_pay":
			dialog.text = "수고해 주셔서 감사합니다. 자, 대가를 받으십시오 - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+".";
		link.l1 = "감사합니다! 거래하게 되어 기쁩니다.";
		link.l1.go = "Contraoffer_complete";
		break;
		
		case "Contraoffer_complete":
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods), sti(pchar.GenQuest.Contraoffer.Trader.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Summ));
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			npchar.quest.Contraoffer.chance = rand(2);//личный шанс торговца для 'пасхалки'
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			if (pchar.GenQuest.Contraoffer.Trader.Chance == 3)
			{
				dialog.text = "이런... 선장님, 여기 문제가 생긴 것 같습니다...";
				link.l1 = "또 뭐요?";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Contraoffer_Patrol");
				pchar.GenQuest.Contraoffer.Trader.busy = "true";
				pchar.quest.Contraoffer_busy.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Contraoffer_busy.win_condition.l1.location = pchar.location;
				pchar.quest.Contraoffer_busy.function = "Trader_free";
			}
			else
			{
				DialogExit();
				AddQuestRecord("Contraoffer", "3");
				CloseQuestHeader("Contraoffer");
				DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
			}
		break;
		
		case "Contraoffer_slaves"://единичный вариант за всю игру, ака 'пасхалка'
			pchar.GenQuest.Contraoffer.Slaves.Name = GetFullName(npchar);
			pchar.GenQuest.Contraoffer.Slaves.Price = 300;//цена на рабов, пока фиксированная, можно подставить формулу
			pchar.GenQuest.Contraoffer.Slaves.Qty = 300+rand(50);//количество
			pchar.GenQuest.Contraoffer.Slaves.Days = 14+rand(6);//срок
			pchar.GenQuest.Contraoffer.Slaves.Money = sti(pchar.GenQuest.Contraoffer.Slaves.Qty)*sti(pchar.GenQuest.Contraoffer.Slaves.Price);
			dialog.text = "노예 한 무더기가 급히 필요하오 - "+sti(pchar.GenQuest.Contraoffer.Slaves.Qty)+" 머리요. 지불할 준비가 되어 있소 "+sti(pchar.GenQuest.Contraoffer.Slaves.Price)+" 영혼 한 명당 동전, 그러면 총합이 "+sti(pchar.GenQuest.Contraoffer.Slaves.Money)+" 총 페소; 기간 - "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days))+".";
			link.l1 = "동의하게 될 것 같군. 번거롭긴 하지만, 아주 이익이 많이 남는 일이야.";
			link.l1.go = "Contraoffer_slaves_1";
			link.l2 = "흥미 없소.";
			link.l2.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;
		
		case "Contraoffer_slaves_1":
			dialog.text = "정말 그렇소 - 이건 아주 수익성이 좋지. 그럼, 노예들과 함께 돌아오기를 기다리겠소.";
			link.l1 = "오래 기다리게 하지 않겠소. 또 봅시다!";
			link.l1.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves.Yes = "begin";
			pchar.GenQuest.Contraoffer.Slaves.City = npchar.city;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "4");
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Slaves.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Slaves.City+"Gen"));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Slaves.Days), false);
		break;
		
		case "Contraoffer_slaves_check":
			amount = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) - GetSquadronGoods(pchar, GOOD_SLAVES);
			if (amount > 0)
			{
				dialog.text = "농담하는 건가? 내가 필요한 노예가 다 없잖아!";
				link.l1 = "죄송합니다, 제 실수였습니다...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "그럼 어디 보자. 나에게 노예 한 무더기를 넘겨주기로 했지, 그 수가 "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty)+". 맞습니까?";
				link.l1 = "정확히 그렇소, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_slaves_pay";
			}
		break;
		
		case "Contraoffer_slaves_pay":
			dialog.text = "수고해 주셔서 감사합니다. 여기 보수 받아 주십시오 - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money))+". 그리고 이것도 받아 주십시오. 분명히 도움이 될 것입니다.";
			link.l1 = "감사합니다! 함께 거래해서 즐거웠습니다.";
			link.l1.go = "Contraoffer_slaves_complete";
		break;
		
		case "Contraoffer_slaves_complete":
			DialogExit();
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(pchar.GenQuest.Contraoffer.Slaves.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Slaves.Money));
			AddQuestRecord("Contraoffer", "5");
			CloseQuestHeader("Contraoffer");
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			AddCharacterExpToSkill(pchar, "Sailing", 150);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			TakeNItems(pchar, "cirass3", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes");
		break;
		// <-- генератор Сомнительное предложение
		
		//Jason --> генератор Неудачливый вор
		case "Device_Trader":
			dialog.text = "흠, "+pchar.GenQuest.Device.Shipyarder.Type+"? 처음 듣는군... 그게 대체 뭔가? 내가 살아오면서 그런 건 한 번도 들어본 적이 없어.";
			link.l1 = "음, 그건 조선공의 도구요, "+pchar.GenQuest.Device.Shipyarder.Describe+". 그런 제안을 누가 했소?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
			{
				dialog.text = "흠... 그래, 이상한 녀석이 한 명 있었지. 그런데 그 자가 그게 뭔지 말해주지도 않고 그냥 나한테 팔려고만 했어. 그런데 내가 그게 뭔지도 모르는데 뭐 하러 사겠나? 어떻게 다시 팔 수 있겠어? 그래서 그냥 거절했지.";
				link.l1 = "그 사람은 어떻게 생겼고, 어디로 갔소? 나는 그 기구가 꼭 필요하오.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "아니, 그런 일은 없어. 미안하지만 도와줄 수 없어. 주변에 물어봐.";
				link.l1 = "알겠소. 자, 이제 사람들에게 물어볼 시간이군!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор

		//Jason --> генератор Место под солнцем
		case "Sunplace_begin":
			dialog.text = "경쟁... 그것 없이는 장사도 없지. 네 아지트 같은 사업에 끼어들려고 별의별 수단으로 손님을 빼앗으려는 욕심 많은 놈들이 있거든.\n뭐, 말이 그렇다는 거지. 사실은 내 경쟁자 중 한 놈을 좀 처리해 줬으면 해서 말이오. 아니, 죽일 필요는 없소. 그냥 그 자의 배와 화물을 나포하거나 침몰시키면 되오.";
			link.l1 = "흠... 뭐, 보수를 잘 준다면 내가 이것을 마련해 줄 수 있지.";
			link.l1.go = "Sunplace_1";
			link.l2 = "아니오, 나는 당신네 상인들 싸움에 끼어들 생각 없소. 내 도움 없이 경쟁자를 침몰시키시오.";
			link.l2.go = "Sunplace_exit";
		break;
		
		case "Sunplace_exit"://если отказал - этот непись больше никогда не даст
			npchar.quest.Sunplace = "true";
			DialogExit();
		break;
		
		case "Sunplace_1":
			GetSunplaceShore();//бухта и остров
			pchar.GenQuest.Sunplace.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");//имя конкурента
			pchar.GenQuest.Sunplace.Trader.Nation = npchar.nation;//нация общая для торговца и конкурента
			pchar.GenQuest.Sunplace.Trader.City = npchar.City;//город квестодателя
			pchar.GenQuest.Sunplace.Trader.CityT = findSunplaceCity(NPChar);//город конкурента
			pchar.GenQuest.Sunplace.Trader.Shiptype = Sunplace_Shiptype();//тип корабля
			pchar.GenQuest.Sunplace.Trader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя корабля
			pchar.GenQuest.Sunplace.Trader.DaysQty = 5 + hrand(5);//дни
			pchar.GenQuest.Sunplace.Trader.Money = sti(pchar.GenQuest.Sunplace.Trader.Shiptype)*3000;//оплата
			pchar.GenQuest.Sunplace.Trader.Goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));//товар
			dialog.text = "알겠습니다. 그러면, 당신 사람의 이름은 "+pchar.GenQuest.Sunplace.Trader.Enemyname+". 최근에 그는 보냈소\n "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Name")+"Acc"))+" '"+pchar.GenQuest.Sunplace.Trader.ShipName+"'에 화물을 싣고 "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+". 그는 이 화물에 꽤 많은 돈을 지불했으니, 이것을 잃는다면 그의 지갑에 큰 타격이 될 것이오.";
			link.l1 = "그 '친구'를 정확히 어디에서 찾아야 하는지 말씀해 주실 수 있습니까?";
			link.l1.go = "Sunplace_2";
		break;
		
		case "Sunplace_2":
			dialog.text = "내 '친구'는 지금 그의 집에 있어, "+XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Voc")+". 그가 필요한 게 아니라 그의 배가 필요하겠지, 내가 알아보니 약 "+FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty))+" 근처를 지나갈 예정이오 "+XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen")+". 침몰시키든, 승선해서 빼앗든 상관없소. 중요한 건 그 배와 화물이 더 이상 그 사람의 소유가 아니게 만드는 것이오\n "+pchar.GenQuest.Sunplace.Trader.Enemyname+". 그리고 그게 당신이든 바다든 누가 차지하든 상관없소. 그 일에 대해서는 내가 돈을 주겠소 "+FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)) + ".";
			link.l1 = "알겠어. 그럼, 이제 출발할 시간이군!";
			link.l1.go = "Sunplace_3";
		break;
		
		case "Sunplace_3":
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "true";
			if (sti(pchar.GenQuest.Sunplace.Chance) == 1 && sti(pchar.rank) > 9) pchar.GenQuest.Sunplace.Bonus = "true";
			ReOpenQuestHeader("Sunplace");
			AddQuestRecord("Sunplace", "1");
			AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
			AddQuestUserData("Sunplace", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)));
			AddQuestUserData("Sunplace", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)));
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.City+"Gen"));
			AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")));
			AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			AddQuestUserData("Sunplace", "sShore", XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen"));
			SetFunctionTimerCondition("Sunplace_Over", 0, 0, sti(pchar.GenQuest.Sunplace.Trader.DaysQty), false);
			pchar.quest.Sunplace_Trader.win_condition.l1 = "location";
			pchar.quest.Sunplace_Trader.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.Island;
			pchar.quest.Sunplace_Trader.win_condition.l2 = "Timer";
			pchar.quest.Sunplace_Trader.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.Sunplace_Trader.win_condition.l2.date.day   = GetAddingDataDay(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.month = GetAddingDataMonth(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.year  = GetAddingDataYear(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.function = "Sunplace_CreateTraderShip";
		break;
		
		case "Sunplace_complete":
			dialog.text = "훌륭하군! 자네라면 믿을 수 있을 거라 생각했지. 그 배와 화물이 어디 있는지는 묻지 않겠네. 어차피 내 알 바가 아니니까. 그리고 내 친구도 그런 충격에서 회복하려면 시간이 꽤 걸릴 걸세, 허허. 자, 여기 돈이네 – 그리고 훌륭하게 일을 마쳐줘서 고맙네.";
			link.l1 = "천만에... 또 봅시다, "+npchar.name+"!";
			link.l1.go = "Sunplace_complete_1";
		break;
		
		case "Sunplace_complete_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "12");
			CloseQuestHeader("Sunplace");
			pchar.GenQuest.Sunplace.Chance = rand(2);
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		case "Sunplace_complete_murder":
			dialog.text = "Poor "+pchar.GenQuest.Sunplace.Trader.Enemyname+", 이런 끔찍한 운명이라니! 그리고 비록 간접적이지만, 그의 죽음의 원인이 바로 나요! 선장, 당신은 이해하지 못하오! 내가 그를 죽이라고 부탁했소? 나는 그가 화물에 쓴 돈을 잃은 뒤 다시... 뭐, 그만두지... 당신은...";
			link.l1 = "이봐, 들어. 그만 징징대라니까? 네가 경쟁자를 없애 달라고 해서 내가 처리했잖아. 더 잘된 거지. 만약 그자가 화물만 잃었다면, 다시 부자가 되어 네 사업에 계속 해를 끼쳤을 거야. 이제 죽은 몸이니 별 수 없겠지.";
			link.l1.go = "Sunplace_complete_murder_1";
		break;
		
		case "Sunplace_complete_murder_1":
			dialog.text = "이제 그만! 더는 못 참겠다! 이런 불경스러운 말을 더 이상 듣고 싶지 않다! 네 피 묻은 돈이나 챙겨서 당장 내 가게에서 나가라!";
			link.l1 = "이봐, "+npchar.name+", 진정 좀 해라, 알겠어? 아니면 내가 직접 네 성질을 식혀주지. 내 검은 항상 내 옆에 있으니까! 좋아, 겁먹지 마라, 그냥 농담이었어. 들어봐, 이렇게 된 건 유감이지만, 애초에 날 속인 건 너였잖아. 그럼 잘 가라.";
			link.l1.go = "Sunplace_complete_murder_2";
		break;
		
		case "Sunplace_complete_murder_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "13");
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			CloseQuestHeader("Sunplace");
			npchar.quest.Sunplace = "true";//этот непись повторно квест больше не даст
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		//Jason --> поиск дезертира
		case "FindFugitiveSt":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 1)
			{
				dialog.text = NPCStringReactionRepeat(""+pchar.GenQuest.FindFugitive.Name+"? 그래, 그 사람 알아. 내게서 장정선에 쓸 식량을 샀지. 낮에는 보통 외진 만에서 낚시를 하고 있지만, 매일 저녁이면 꼭 선술집에 있더군.","그 남자에 대해 이미 나에게 물었고, 내가 아는 건 전부 말했소!","농담하는 거야, 아니면 진짜 바보인 거야?! 같은 질문을 벌써 세 번째 하고 있잖아!","어떻게 저런 바보가 선장이 될 수 있었을까, 생각만 해도 한심하군...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("감사합니다, 정말 큰 도움이 되었어요!","그래, 그래, 알았어.","자, 자, 그렇게 흥분하지 마. 그냥 깜빡했을 뿐이야.","글쎄, 보시다시피 그는 그렇게 했소...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("포트 로얄 선술집에서 사람들이 무슨 말을 했는지는 모르겠지만, 나는 그 남자를 내 가게에서 만난 적이 없어. 사실 어디서도 본 적이 없네. 마을 사람들에게 물어보게나 - 어쩌면 누군가가 말해줄지도 모르지...","그 남자에 대해서 이미 나에게 물었고, 나는 모른다고 말했소!","나를 놀리는 거요, 아니면 정말 바보요?! 같은 질문을 벌써 세 번째나 하고 있잖소!","어떻게 저런 바보가 선장이 됐는지, 생각만 해도 어이가 없군...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("알겠소. 그래도 감사하오.","그래, 그래, 알았어.","자, 자, 그렇게 흥분하지 마. 그냥 깜빡했을 뿐이야.","글쎄, 보시다시피 그는 그렇게 했소...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveSt_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-2");
			sld = characterFromId("Fugitive");
			LAi_SetSitType(sld);
			sld.dialog.currentnode = "Fugitive_tavern";
			LAi_SetLoginTime(sld, 20.0, 23.99);
			FreeSitLocator(pchar.GenQuest.FindFugitive.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_tavern", "sit", "sit_front1");
		break;
		//<-- поиск дезертира
		
		// --> Карибские нравы - временное завершение
		// belamour legendary edition -->
		case "trial":
			dialog.text = "나리, 대체 왜 그러십니까, 젊은이! 제발 언행을 삼가고 존경받는 분들에 대해 말할 때는 조심하십시오! 제라르 르크루아는 본토로 원정대를 이끌고 과들루프를 떠났지만, 당신의 보상은 여기 남겨두고 갔소. 이제 만족하십니까?";
			link.l1 = "흠... 실례했습니다, 나리. 제가 좀 흥분했군요...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "아주 좋습니다. 르크루아 나리가 당신의 보상을 지역 등대지기에게 맡겼습니다. 두 사람은 오랜 친구라더군요. 그를 찾아가서 보상을 받기만 하면 됩니다. 르크루아 나리는 정직한 분이니, 보상에 만족하실 거라 생각합니다.";
			link.l1 = "알겠어요, 고마워요! 그럼 등대지기에게 가볼게요. 이제 잠깐 쉬게 해주세요.";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			//TakeNItems(pchar, "gold_dublon", 400);
			link.l1 = "...";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "trialA":
			dialog.text = "예, 그는 여기서 당신을 기다리고 있었소. 하지만 그가 맡긴 일이 예상보다 더 어려웠던 모양이오, 그래서 기다리지 않고 본토로 원정에 나섰소. 당신의 보상은 믿을 만한 사람에게 맡기고 갔소.";
			link.l1 = "예, 정말 예기치 못한 일이 있었지만 임무는 성공적으로 완수했습니다. 제 보수가 기다리고 있다니 기쁘군요. 누구에게서 받아야 합니까?";
			link.l1.go = "trialA_1";
		break;
		
		case "trialA_1":
			dialog.text = "르크루아 씨가 당신의 보상을 현지 등대지기에게 맡겼소 – 두 사람은 오랜 친구라 하더군. 당신은 그를 찾아가 보상만 받으면 되오. 르크루아 나리는 정직한 분이니, 보상에 만족할 거라 생각하오.";
			link.l1 = "알겠어요, 고마워요! 그럼 등대지기에게 가볼게요. 이제 잠깐 쉬게 해줘요.";
			link.l1.go = "trialA_2";
		break;
		
		case "trialA_2":
			dialog.text = "행운을 빕니다, 나리.";
			link.l1 = "...";
			link.l1.go = "trialA_3";
		break;
		
		case "trialA_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Commerce", 80);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- legendary edition
		/*case "trial":
			dialog.text = "이런, 왜 이렇게 시끄럽소, 젊은이! 진정하고, 존경받는 분들에 대해 말할 때는 언행을 조심하시오! 제라르 르크루아는 본토로 원정을 떠나며 과달루프를 떠났지만, 그가 당신에게 전할 메시지를 남겼소\n이제 진정했소, 나리? 내 말을 들을 준비가 되었소?";
			link.l1 = "흠... 실례했소, 나리. 내가 좀 흥분했군. 듣고 있소.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "아주 좋소. 다음에는 먼저 물어보고, 그 다음에 크게 소리치도록 하시오. 좋아... Simon Maurois라는 이름의 남자를 아시오?";
			link.l1 = "하! 시몽 모루아를 모르는 사람이 어디 있겠소! 물론 알고 있지.";
			link.l1.go = "trial_2";
			link.l2 = "그 사람은 처음 듣는데. 누구지?";
			link.l2.go = "trial_3";
		break;
		
		case "trial_2":
			dialog.text = "훌륭하오. 그에게 가시오. 쇼크 나리의 원정에 자금을 댄 사람이 바로 그이니, 그에게서 보상을 받으면 되오. 그런데, 그렇게까지 흥분할 필요가 있었소?";
			link.l1 = "다시 한 번 용서를 구합니다... 도와주셔서 감사합니다, 나리. 즉시 마루아 나리를 뵙겠습니다!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_3":
			dialog.text = "그는 마루아 은행가의 주인이자 캡스터빌 지점의 책임자요. 그러니 생크리스토퍼로 가서 캡스터빌 은행을 방문해야 하오. 쇼크 나리의 원정에 자금을 댄 것도 바로 마루아 나리였으니, 그에게서 보상을 받을 수 있소. 그러니, 그렇게까지 흥분할 필요가 정말 있었소?";
			link.l1 = "다시 한 번 용서를 구합니다... 도와주셔서 감사합니다, 나리. 지금 바로 마루아 나리를 뵙겠습니다!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_exit":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.Trial = "usurer";
			AddQuestRecord("Trial", "22");
		break;*/
		
		// belamour legendary edition на пару с Акулой -->
		case "SharkGoldFleet":
			dialog.text = "아, 진취적인 상인님이시군요! 사업 수완이 한눈에 보입니다. 존경스럽습니다. 물론, 원하시는 물건은 다 준비되어 있지요.";
			link.l1 = "분명 이걸 팔아서 이익을 남길 수 있겠군. 내가 알기로는 포르토 벨로에서 이 상품의 수요가 높소. 내게 얼마에 팔겠소?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			pchar.questTemp.SharkGoldFleet = "buyincar";
			dialog.text = "그저 그렇군... 자, 커피 300단위... 그리고 같은 양의 코코아... 그 값이 나오겠군..."+sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_COFFEE,PRICE_TYPE_BUY,pchar,300)+GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_CHOCOLATE,PRICE_TYPE_BUY,pchar,300))+" 페소!";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "흠... 실례합니다만, 지금 현금이 좀 부족하군요. 잠시만 기다려 주십시오. 지금 배에 가서 돈을 가져오겠습니다 - 곧 돌아오겠습니다!";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "여기 있습니다.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		
		case "SharkGoldFleet_02":
			if(GetCargoFreeSpace(pchar) < 1200)
			{
				dialog.text = "잠깐만요, 나리. 당신 배에 그런 인원을 태울 공간이 부족한 것 같소. 창고를 비우고 다시 오시오.";
				link.l1 = "아, 짐을 내리는 걸 깜빡했네! 잠깐만 기다려, 금방 갈게!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "좋습니다! 곧바로 당신 배에 물건을 싣도록 명령하겠습니다. 함께 거래하게 되어 기쁩니다!";
				link.l1 = "저도 그렇소, 나리! 이제 실례하겠소. 일이 기다려주지 않으니.";
				link.l1.go = "SharkGoldFleet_03";
			}
		break;
		
		case "SharkGoldFleet_03":
			DialogExit();
			AddMoneyToCharacter(pchar, -sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE)+300);
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE)+300);
			AddQuestRecord("SharkGoldFleet", "4");
			pchar.questTemp.SharkGoldFleet = "toCarPortOffice";
		break;
		
		case "SharkGoldFleet_again":
			dialog.text = "물건이 준비되어 있소. 돈은 가져왔소?";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "아직 아닙니다. 그냥 당신의 제안이 여전히 유효한지 확인하고 싶었을 뿐입니다. 그리고 돈은 곧 들어올 겁니다.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "여기 있습니다.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		//<-- на пару с Акулой
		case "no_quests":
			dialog.text = "지금은 당신의 서비스가 필요하지 않습니다.";
			link.l1 = "안타깝군. 화제를 바꿔보지.";
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":			
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();			
		break;
	}
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
			if (NPChar.id == "SanAndres_trader" || ch.id == "SanAndres_trader") continue; // fix 2016-03-07
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // хрен вам, а не читы!
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int Sunplace_Shiptype() // new
{
	int i;
	
	if (sti(pchar.rank) >= 1 && sti(pchar.rank) < 6) i = SHIP_SCHOONER;
	if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 11) i = SHIP_FLEUT;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 18) i = SHIP_PINNACE;
	if (sti(pchar.rank) >= 18) i = SHIP_GALEON_L;
	
	return i;
}

string findSunplaceCity(ref NPChar) // new
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
