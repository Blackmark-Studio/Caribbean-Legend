// boal 08/04/06 общий диалог верфи
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	string s2;
	
	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернет 7 (лодка)
	int iRank = sti(PChar.rank);
	int iSumm, iType;
	
	ref rRealShip;
	ref shTo;
	aref refShip;
	string attr;
	float fTmp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int Material, WorkPrice;
	int amount;
	int	iCannonDiff;
	
	// генератор парусов по кейсу -->
	string attrLoc   = Dialog.CurrentNode;
	int i;
  	if (findsubstr(attrLoc, "SailsColorIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (findsubstr(attrLoc, "SailsTypeChooseIDX_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
	if(!CheckAttribute(NPChar, "ExpMeeting"))
	{
		NPChar.ExpMeeting = true;
		notification("First Shipyard Visit " + XI_ConvertString("Colony" +NPChar.City + "Gen"), "Carpenter");
		AddCharacterExpToSkill(pchar, SKILL_REPAIR, 10.0);
	}
 	// генератор парусов по кейсу <--
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // аналог выхода, со старых времен, много переделывать.
            LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  // выход для тюнинга, нужно тут из-за LoadSegment
		break;
		
		case "ship_tunning_not_now_1":  
			LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("마을에 경보가 울려서 모두가 너를 찾고 있어. 내가 너라면 여기 안 머물겠어.","도시 경비병 전원이 너를 찾으려고 마을을 샅샅이 뒤지고 있다. 나도 바보는 아니니 너랑 말하지 않겠다!","달려라, "+GetSexPhrase("동료","아가씨")+", 군인들이 널 벌집으로 만들기 전에..."),LinkRandPhrase("무엇이 필요하시오, "+GetSexPhrase("놈","악취 나는 놈")+"?! 도시 경비병들이 이미 네 냄새를 맡았어, 더 이상 못 도망가, 더러운 해적놈!","살인자야, 당장 내 집에서 나가라! 경비병들!","난 너 따위 안 무서워, "+GetSexPhrase("놈","쥐")+"! 곧 우리 요새에서 목이 매달릴 거다, 멀리 못 갈 테니..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("헤, 경보 따위 나한텐 문제도 아니지...","걔네들은 절대 나를 못 잡을 거야."),RandPhraseSimple("입 다물어, "+GetWorkTypeOfMan(npchar,"")+", 아니면 네 혀를 뽑아버릴 거야!","헤헷, "+GetWorkTypeOfMan(npchar,"")+", 그리고 거기서도 해적을 잡으라고! 내가 말하는 거야, 친구야: 조용히 있으면 죽지 않아!"));
				link.l1.go = "fight";
				break;
			}
			
//Jason ---------------------------------------Бремя гасконца------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_shipyard")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
				{
					dialog.text = "무엇을 원하십니까, 나리?";
					Link.l1 = "네 배들을 좀 보러 왔는데... 지금은 좀 바빠. 아직 끝내지 못한 일이 있거든. 그거 끝나면 다시 올게.";
					Link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
				{
					dialog.text = "무엇을 원하십니까, 나리?";
					Link.l1 = "이봐, 너한테서 배를 사고 싶은데.";
					Link.l1.go = "Sharlie";
					break;
				}
				dialog.text = "다른 필요한 것이라도 있습니까, 나리?";
				Link.l1 = "아니, 그렇진 않겠지.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				NPChar.quest.meeting = "1";
				break;
			}
	//<-- Бремя гасконца
			// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
			if (CheckAttribute(pchar, "questTemp.FMQM.Oil") && pchar.location == "Fortfrance_shipyard")
			{
				if (pchar.questTemp.FMQM == "remove_oil")
				{
					dialog.text = "여기까지입니다, 선장님. 일은 끝났습니다. 이제 즐거운 부분이 남았군요 - 동전 소리 말입니다. 잠깐만 기다리십시오...";
					link.l1 = "...";
					link.l1.go = "FMQM_oil_1";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil1")
				{
					dialog.text = "장교님, 잠깐만요! 제발요! 이건 뭔가 착오가 있는 것 같습니다. 나리, 선장님은 이 일과 아무런 관련이 없습니다. 그는 단지 배를 수리하려고 여기 정박했을 뿐입니다. 이제 막 떠나려던 참이었어요. 그리고 무슨 통을 말씀하시는 거죠? 무슨 이야기입니까?";
					link.l1 = "";
					link.l1.go = "FMQM_oil_2";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil2")
				{
					dialog.text = "장교 양반, 다시 말하겠소: 선장님께서 배 수리비를 지불하러 오신 거요. 이 통들은 내 재산이며 오직 생산 목적으로만 쓰이는 것이오. 나는 숙련된 조선공이고, 이 송진은 내가 만드는 선박을 위해 필요한 거요.";
					link.l1 = "";
					link.l1.go = "FMQM_oil_3";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil3")
				{
					dialog.text = "아, 선장 나리! 내가 얼마나 끔찍한 시간을 보냈는지 상상도 못 하실 겁니다. 쥐와 생쥐, 비참한 놈들로 가득한 지하 감옥에서 이틀이나 있었어요! 거기서 빠져나오려고 내가 가진 모든 인맥을 다 써야 했지요. 아, 이 신선한 공기!";
					link.l1 = "안됐군요, 주인장. 우리 송진은 어쩌죠? 그리고 내 돈은?";
					link.l1.go = "FMQM_oil_4";
					DelLandQuestMark(npchar);
					break;
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_13" && pchar.location == "PortRoyal_shipyard")
			{
				dialog.text = "오, 또 왔구나! 알아보겠어, 젊은이! 얼마 전에 네가... 비단 돛천으로 배의 속도를 높이는 방법을 물었던 그 녀석 맞지?";
				link.l1 = "기억력이 훌륭하시군요, 주인장."; 
				link.l1.go = "mtraxx_x";
				break;
			}
			
			if(NPChar.quest.meeting == "0") // первая встреча
			{
				dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("하! 진짜 노련한 뱃사람이 내 보잘것없는 작업장에 찾아왔군! 이 바다에는 처음이오, 선장?","어서 오십시오, 나리! 바다에 익숙하고 배가 있다면, 바로 제대로 찾아오셨습니다!","안녕하세요, 나리! 운이 좋으십니다 – 여기가 영국 신세계에서 가장 훌륭한 조선소입니다."),LinkRandPhrase("나리, 당신은 멋진 선장 맞지요? 그렇다면 내 소박한 조선소에 찾아온 건 잘한 일이오!","여기 처음이오, 선장 나리? 들어와서 이 늙은 조선공을 만나보시오.","서로 알아가는 즐거움을 누려봅시다, 나리! 배란 건 여자처럼 다루어야 하오. 우리 프랑스인들은 그 방면의 달인이지! 나를 믿으시오, 여기 온 걸 후회하지 않을 것이오!"),LinkRandPhrase("여기서 처음 뵙는군, 나리. 만나서 반갑소!","바다를 정복한 용감한 분을 맞이하오! 그대는 선원이겠지? 나는 이곳의 조선공이오. 서로 알아두는 게 좋겠군.","안녕하세요, 카바예로! 제 작업장에 오신 것을 환영합니다!"),LinkRandPhrase("안녕하세요, 마인헤르. 전에 뵌 적이 없었던 것 같은데요? 무슨 일로 오셨습니까?","안녕하시오, 선장 나리. 놀라지 마시오, 내가 선장들을 꽤 많이 만나봤기에 처음 보자마자 당신도 선장임을 알았소.","들어오시지요, 나리. 나는 이곳의 조선공이오. 만나서 반갑소."));
				Link.l1 = LinkRandPhrase("나도 만나서 반갑소. 내 이름은 "+GetFullName(pchar)+", 그리고 나는 이 근방에 처음이오. 그래서 한번 들러 보기로 했소.","그냥 지나칠 수가 없었지 – 알잖아, 갓 깎은 판자 냄새가... 나는 "+GetFullName(pchar)+", '의 선장"+pchar.ship.name+"'.","자기소개를 하겠습니다 - "+GetFullName(pchar)+", ' 선장"+pchar.ship.name+", 만나서 반갑소. 여기서 배를 만들고 수리하는 거지?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_shipyard")
				{
					dialog.text = "안녕하십니까, MacArthur 선장.";
					link.l1 = "그냥 헬렌이라고 불러도 돼요, 나리 "+npchar.lastname+". "+TimeGreeting()+".";
					Link.l1.go = "Helen_meeting";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("오! 이 지역 바다의 공포로군요, 선장 "+GetFullName(pchar)+"! 무엇을 도와드릴까요?","바로 본론으로 들어가자, "+GetAddress_Form(NPChar)+", 잡담할 시간 없어. 수리를 원해? 아니면 그냥 네 배를 바꾸고 싶은 거야?","오, 그거 아니냐 "+GetFullName(pchar)+"! 무슨 일이야, "+GetAddress_Form(NPChar)+"뭐야? 네 배에 무슨 문제라도 생겼나?"),LinkRandPhrase("지금 또 뭘 원하시오, 선장? 잠시도 쉴 틈이 없구만 – 맨날 이런 악당들 때문에, 저주받을 날이로군...","안녕하세요, "+GetAddress_Form(NPChar)+". 솔직히 말해서, 당신이 오자 내 손님들이 다 도망갔소. 주문이 내 손해를 메꿔 줄 수 있겠지?","나와 볼일이 있어서, "+GetAddress_Form(NPChar)+"? 그럼, 어서 해. 빨리 끝내라."),LinkRandPhrase("무슨 일로 나를 찾았소, 나리 "+GetFullName(pchar)+"? 네 생활 방식을 생각하면 네 배가 고생하는 것도 이해가 가는군...","고귀한 분을 맞이하게 되어 기쁩니다... 아, 실례했습니다, "+GetAddress_Form(NPChar)+", 내가 다른 사람으로 착각했군. 무슨 일로 왔지?","난 너 같은 부류는 별로 좋아하지 않네, 선장. 그래도 내쫓진 않겠어. 무슨 일로 왔지?")),LinkRandPhrase(LinkRandPhrase("당신을 만나서 정말 반갑습니다, 나리 "+GetFullName(pchar)+"! 자, 배는 잘 나가나? 수리나 켈링이 필요해?","어서 오시오, "+GetAddress_Form(NPChar)+"! 선장님 "+GetFullName(pchar)+" 내 작업장에 언제나 환영받는 손님이오!","오, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! 또 나를 찾아왔군! 네 배는 잘 있지, 그렇지?"),LinkRandPhrase(""+GetAddress_Form(NPChar)+", 다시 만나서 정말 반갑소! 멋진 배는 잘 있소? 도움이 필요하오?","오, "+GetAddress_Form(NPChar)+", 안녕하시오! 별일 없으신가? 돛대가 삐걱거리진 않는지, 아니면 선창 청소가 필요하신가? 우리 사람들이 최선을 다해 드릴 것이오!","좋은 오후입니다, 선장님 "+GetFullName(pchar)+". 다시 찾아와 주셔서 기쁩니다, 언제든 도와드릴 준비가 되어 있습니다."),LinkRandPhrase("여기 와 주셔서 기쁩니다, 선장님! 당신은 정말 반가운 손님이십니다, "+GetAddress_Form(NPChar)+", 그리고 앞으로도 그렇게 남아 있기를 바랍니다.","오, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! 당신이 여기 와서 정말 기쁩니다! 무엇을 도와드릴까요?","선장님, 또 오셨군요 "+XI_ConvertString("Colony"+npchar.City+"Acc")+"! 믿어 주시오, 우리가 기꺼이 도와주고 싶소.")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("도구 챙겨, 주인장, 그리고 조용히 해, 알겠어? 지금 기분 안 좋으니까.","쓸데없는 소리 집어치워, 이봐! 네 도움이 필요하지, 잡담은 필요 없어."),RandPhraseSimple("내가 돈을 내고, 너는 일하는 거다. 말없이. 알겠나?","이봐, 친구, 다 내보내! 나야, 네가 제일 좋아하는 손님!")),RandPhraseSimple(RandPhraseSimple("나도 만나서 반갑소, 나리. 유감스럽게도 시간이 많지 않으니, 본론으로 들어갑시다.","나도 너를 다시 보게 되어 기쁘다, 친구. 네가 제일 좋아하는 손님 좀 도와줄래?"),RandPhraseSimple("좋은 오후야, 친구. 바로 본론으로 들어가자. 다음번엔 꼭 한 병 같이 하자고 약속할게.","당신을 뵙게 되어 기쁩니다, 나리. 항상 만나서 반갑지만, 지금은 당신의 도움이 필요합니다.")));
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l11 = "내 배에 쓸 대포가 필요해.";
					link.l11.go = "Cannons";					
				}	
				
				if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "Charles" || NPChar.city == "PortoBello")
				{
					link.l22 = "다른 어느 조선소에서도 찾을 수 없는 특별한 무언가를 내게 줄 수 있겠소?";
					link.l22.go = "ship_tunning";
				}
				
				link.l15 = "낯선 이의 도움이 필요한 일은 없소?";
			    link.l15.go = "Tasks";
				// Jason Исла Мона 
				if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "tools" && !CheckAttribute(npchar, "quest.IslaMonaTools"))
				{
					link.l20 = "고급 유럽산 건축, 단조, 측량 도구 세트를 사고 싶은데, 도와줄 수 있겠소?";
					link.l20.go = "IslaMona";
				}
				if (CheckAttribute(npchar, "quest.IslaMonaMoney"))
				{
					link.l20 = "건축 도구 세트 값을 두블룬으로 가져왔소.";
					link.l20.go = "IslaMona_7";
				}
				//Jason --> генератор Призонер
				if (CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && NPChar.location == pchar.GenQuest.Findship.Shipyarder.City + "_shipyard")
				{
					ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
					if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
					{
						for(i = 1; i < COMPANION_MAX; i++)
						{
							int iTemp = GetCompanionIndex(PChar, i);
							if(iTemp > 0)
							{
								sld = GetCharacter(iTemp);
								if(GetRemovable(sld) && sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.GenQuest.Findship.Shipyarder.ShipType))
								{
									pchar.GenQuest.Findship.Shipyarder.CompanionIndex = sld.Index;
									pchar.GenQuest.Findship.Shipyarder.OK = 1;
									pchar.GenQuest.Findship.Shipyarder.ShipName = sld.Ship.Name;
									pchar.GenQuest.Findship.Shipyarder.Money = makeint(GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder"))*1.5);
								}
							}
						}
					}
					if (sti(pchar.GenQuest.Findship.Shipyarder.OK) == 1)
					{
						link.l16 = "내가 너한테 전달했어 "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+", 요청하신 대로입니다.";
						link.l16.go = "Findship_check";
					}// <-- генератор Призонер
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && CheckCharacterItem(pchar, "Tool") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_shipyard")
				{
					link.l17 = "도둑을 찾아내서 되찾아왔어 "+pchar.GenQuest.Device.Shipyarder.Type+".";
					link.l17.go = "Device_complete";
				}
				// <-- генератор Неудачливый вор
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "내 돛의 모습을 바꾸고 싶어.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "그냥 얘기나 좀 하려고 했어.";
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "재정 문제에 대해 이야기하고 싶소.";
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("나는 한 남자의 부탁을 받고 여기 왔다. 그의 이름은 총독이다\n "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" 나를 당신에게 보냈어. 내가 뭔가를 받아가야 한다는데...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "배 도면을 가져왔소, 출처는 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				} // patch-6
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = "안녕하세요, 아드님의 초대로 왔습니다."; 
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = "이건 당신 딸에 관한 일이오...";
							link.l8.go = "EncGirl_1";
						}
					}
				}								
				Link.l9 = "가야겠다.";
				Link.l9.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Meeting":
				dialog.Text = "새로운 손님을 만나서 정말 반갑소. 내 조선소가 당신을 위해 준비되어 있소.";
				Link.l1 = "훌륭하군, "+GetFullName(NPChar)+". 네가 내게 뭘 내놓을 수 있는지 보자.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "내 배에 쓸 대포가 필요해.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "낯선 이의 도움이 필요한 일은 없소?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "내 돛의 모습을 바꾸고 싶어.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "그냥 얘기나 좀 하려고 했어.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "재정 문제에 대해 이야기하고 싶소.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("나는 한 사람의 부탁을 받고 여기 왔다. 그의 이름은 총독이다 "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" 나를 당신에게 보냈어. 뭔가를 받아가라고 했는데...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "나는 그 배의 도면을 그 마을에서 가져왔어 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "안녕하세요, 아드님의 초대로 왔습니다."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "이건 당신 딸에 관한 일이오...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "이 서류의 주인에 대해 무엇을 말해줄 수 있지?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "가봐야겠소. 감사합니다.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;
		
		case "Helen_Meeting":
				dialog.Text = "물론입니다, MacArthur 선장님, 원하시는 대로 하겠습니다. 오늘은 무엇이 필요하십니까?";
				Link.l1 = "훌륭하군, "+GetFullName(NPChar)+". 자, 뭘 내게 내놓을 수 있는지 보자.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "내 배에 쓸 대포가 필요해.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "낯선 이의 도움이 필요한 일은 없소?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "내 돛의 모양을 바꾸고 싶어.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "그냥 얘기나 좀 하려고 했어.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "재정 문제에 대해 이야기하고 싶소.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("나는 한 사람의 부탁을 받고 여기 왔다. 그의 이름은 총독이다 "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" 나를 당신에게 보냈어. 뭔가를 받아가라고 했는데...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "나는 그 배의 도면을 그 마을에서 전달했어 "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "안녕하세요, 아드님의 초대로 왔습니다."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "이건 당신 딸에 관한 일이오...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "이 서류의 주인에 대해 무엇을 말해줄 수 있소?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "가봐야겠소, 고맙소.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;

		case "ship_tunning":
			dialog.text = "우리 조선소는 선박 개조로 유명하지. 관심 있나, 선장?";
			Link.l1 = LinkRandPhrase("훌륭하군! 내 배를 한번 봐주고 어떻게 더 나아질 수 있을지 말해줄 수 있겠나?","아주 흥미로운데, 주인장! 내 배를 위해 뭘 해줄 수 있지?","흠... 내 배에 정이 좀 들었지만, 정말 흥미로운 제안을 한다면 생각해 볼 수도 있지. 어때?");
			Link.l1.go = "ship_tunning_start";
		break;
				
		case "ship_tunning_start" :		
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{				
				if (sti(RealShips[sti(pchar.Ship.Type)].Class) >= 7)
				{
					dialog.Text = "으으... 나는 보트는 안 다뤄. 낡은 통은 아무리 손봐도 결국 낡은 통일 뿐이야.";
					Link.l1 = "그렇군...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// belamour legendary edition -->
				if(!TuningAvailable())
				{
					dialog.Text = "그저 그렇군... 어디 한번 볼까... 그래 - "+XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName)+". 당신 배는 이미 최대한으로 개조되어 있소. 더 이상 손을 대는 건 의미가 없고, 오히려 해가 될 수도 있겠구려.";
					Link.l1 = "그렇군...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// <-- legendary edition							
				if(GetHullPercent(pchar) < 100 || GetSailPercent(pchar) < 100)
				{
					dialog.Text = "배를 개조하기 전에 완전히 수리해야 하오. 이것 또한 내 조선소에서 할 수 있소.";
					Link.l1 = "알겠습니다...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				
				s2 = "Alright, let's see what we've got here... Aha " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
				// belamour legendary edition -->
				if(NPChar.city == "PortRoyal")
				{
					s2 = s2 + " Our shipyard is famous for improving the ship's performance we can increase either the maximum speed or the angle to the wind.";
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					s2 = s2 + " At our shipyard we can increase the maximum number of cannons or the ship's carrying capacity.";
				}
				if(NPChar.city == "Villemstad")
				{
					s2 = s2 + " My guys can reinforce the hull of your ship or increase the maximum number of sailors in your crew.";
				}
				if(NPChar.city == "Charles")
				{
					s2 = s2 + " At this shipyard you can improve the maneurability or decrease the minimum number of sailors in the crew.";
				}	
				
				dialog.Text = s2;
				
				if(NPChar.city == "PortRoyal")
				{
					// belamour legendary edition -->
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"));
					if(ok)
					{
						Link.l1 = "속도를 높여라.";
						Link.l1.go = "ship_tunning_SpeedRate";
						Link.l2 = "바람에 대한 각도를 더 키워라.";
						Link.l2.go = "ship_tunning_WindAgainst";
						Link.l3 = "잠깐! 마음이 바뀌었어.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
						{
							Link.l1 = "속도를 올려라.";
							Link.l1.go = "ship_tunning_SpeedRate";
							Link.l2 = "잠깐! 마음이 바뀌었어.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"))
						{
							Link.l1 = "바람에 대한 각도를 더 키워라.";
							Link.l1.go = "ship_tunning_WindAgainst";
							Link.l2 = "잠깐! 마음이 바뀌었어.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("오! 내 배는 이미 이렇게 개조됐어. 그래도 시간 내줘서 고마워!","고맙소, 주인장. 하지만 이미 업그레이드는 가지고 있고, 당신이 말한 바로 그거요. 다른 배들과 그 선장들에게도 행운이 있길 바라오!","헤헤! 내 생각엔 내 배가 이미 이전 선주에 의해 개조된 것 같군 - 바로 이 조선소에서였겠지. 뭐, 그의 선견지명에 감사해야겠고, 자네와 자네 일꾼들의 훌륭한 솜씨에도 감사해야겠어!");
						Link.l1.go = "ship_tunning_not_now_1";					
					}
						// <-- legendary edition
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"));
					if(ok)
					{	
						if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
						{	
							Link.l1 = "대포 최대 수를 늘리시오.";
							Link.l1.go = "ship_c_quantity";
						}	
							Link.l2 = "적재중량을 늘려라.";
							Link.l2.go = "ship_tunning_Capacity";
						Link.l3 = "잠깐! 마음이 바뀌었어.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
						{
							if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
							{	
								Link.l1 = "대포 최대 수를 늘리시오.";
								Link.l1.go = "ship_c_quantity";
								Link.l2 = "잠깐! 마음이 바뀌었어.";
								Link.l2.go = "ship_tunning_not_now_1";	
								break;
							}	
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
						{
							Link.l1 = "적재중량을 늘려라.";
							Link.l1.go = "ship_tunning_Capacity";
							Link.l2 = "잠깐! 마음이 바뀌었어.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("오! 내 배는 이미 이렇게 개조되어 있군. 그래, 시간 내줘서 고맙다!","고맙소, 주인장. 하지만 이미 업그레이드를 했고, 당신이 말한 바로 그거요. 다른 배들과 그 선장들에게도 행운이 있길 바라오!","헤! 내 배가 이미 이전 선주에 의해 개조된 모양이군. 아마 바로 이 조선소였겠지. 뭐, 그 선주의 선견지명에 감사해야겠고, 당신과 일꾼들의 훌륭한 솜씨에도 감사해야겠어!");
						Link.l1.go = "ship_tunning_not_now_1";	
					// <-- legendary edition
					}						
				}
				if(NPChar.city == "Villemstad")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"));
					if(ok)
					{
						Link.l1 = "선체의 내구도를 높여라.";
						Link.l1.go = "ship_tunning_HP";
						Link.l2 = "승무원 공간을 늘린다.";
						Link.l2.go = "ship_tunning_MaxCrew";
						Link.l3 = "잠깐! 마음이 바뀌었어.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
						{
							Link.l1 = "선체의 내구도를 높이시오.";
							Link.l1.go = "ship_tunning_HP";
							Link.l2 = "잠깐! 마음이 바뀌었어.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
						{
							Link.l1 = "선원 공간을 늘려라.";
							Link.l1.go = "ship_tunning_MaxCrew";
							Link.l2 = "잠깐! 마음이 바뀌었어.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;	
						}
						Link.l1 = LinkRandPhrase("오! 내 배는 이미 이렇게 개조되어 있네. 그래, 시간 내줘서 고마워!","고맙소, 주인장. 하지만 이미 업그레이드를 했고, 바로 전에 말씀하신 그것이오. 다른 배들과 선장들에게도 행운이 있기를!","헤헤! 내 생각엔 내 배가 이전 주인에 의해 이미 개조된 것 같군 - 바로 이 조선소에서였겠지. 뭐, 그 사람의 선견지명에 감사해야겠고, 자네와 일꾼들의 훌륭한 솜씨에도 고마워해야겠군!");
						Link.l1.go = "ship_tunning_not_now_1";	
						// <-- legendary edition
					}
				}
				if(NPChar.city == "Charles")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"));
					if(ok)
					{		
						Link.l1 = "조타 성능을 높여라.";
						Link.l1.go = "ship_tunning_TurnRate";
						if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
						{
							Link.l2 = "최소 선원 수를 줄이시오.";
							Link.l2.go = "ship_tunning_MinCrew";
						}	
						Link.l3 = "잠깐! 마음이 바뀌었어.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
						{
							Link.l1 = "조종성을 높여라.";
							Link.l1.go = "ship_tunning_TurnRate";
							Link.l2 = "잠깐! 마음이 바뀌었어.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"))
						{
							if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
							{
								Link.l1 = "최소 선원 수를 줄여라.";
								Link.l1.go = "ship_tunning_MinCrew";
								Link.l2 = "잠깐! 마음이 바뀌었어.";
								Link.l2.go = "ship_tunning_not_now_1";
								break;
							}	
						}
						// <-- legendary edition				
					}
					Link.l1 = LinkRandPhrase("오! 내 배는 이미 이렇게 개조되어 있소. 자, 시간 내줘서 고맙소!","고맙소, 주인장. 하지만 이미 업그레이드를 했고, 당신이 말한 바로 그거요. 다른 배들과 그 선장들에게도 행운이 있길 바라오!","헤! 내 배가 이미 이전 주인에 의해 개조된 모양이군. 분명 이 조선소에서 했던 거겠지. 뭐, 그 사람의 선견지명에 감사해야겠고, 자네와 일꾼들의 훌륭한 솜씨에도 감사를 표해야겠군!");
					Link.l1.go = "ship_tunning_not_now_1";	
				}								
			}
			else
			{
				dialog.Text = "배는 어디 있지? 지금 나 놀리는 거야, 뭐야?";
			    Link.l1 = "아, 내 실수였군... 정말 미안하오.";
			    Link.l1.go = "ship_tunning_not_now_1";
			}			
		break;
		
		////////////////////////////////////////// Capacity ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Well, let's see what we can do. At the moment the deadweight of your vessel is " + sti(RealShips[sti(pchar.Ship.Type)].Capacity);			
			s2 = s2 + ". For lighter bulkheads I will require: ironwood - " + Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";			
            dialog.Text = s2;
			Link.l1 = "알겠소. 조건을 받아들이겠소. 필요한 건 뭐든 가져오겠소.";
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = "아니. 그건 내 마음에 들지 않아.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_Capacity_start":
		    amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;			    
				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.text = "훌륭하군. 자재를 기다리고 있겠네.";
			    link.l1 = LinkRandPhrase("오래 기다릴 필요 없다는 걸 보장하오. 이런 문제는 내가 바로 해결할 수 있소, 알겠소?","이미 그들을 데리고 있다고 생각하고 나를 위해 부두를 잡아 두시오. 나는 바람처럼 빠르게 올 것이오.","물론이지. 네가 부탁한 물건을 가진 사람 몇 명만 만나고 오면 돼, 하하!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the tonnage of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'"+
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "나는 보증금을 못 봤는데...";
				link.l1 = "나중에 들르겠소.";
				link.l1.go = "Exit";								
			}
		break;
				
		case "ship_tunning_Capacity_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "시간이 흐르고, 배는 기다리고 있소. 내가 부탁한 것들 다 가져왔소?";
			    Link.l1 = "그래, 뭔가 찾아냈어.";
			    Link.l1.go = "ship_tunning_Capacity_again_2";
			    Link.l2 = "아니, 아직 작업 중이오.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
			    dialog.Text = "Mis"+GetSexPhrase("터","s")+", 우리가 약속한 이후로 배를 바꾼 건가? 그러면 안 됐는데.";
			    Link.l1 = "아, 이게 다 상황 때문이지! 보증금이 날아가 버려서 안타깝군...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "훌륭하군, 이제 필요한 건 다 모였어. 그럼 작업을 시작하지.";
			    link.l1 = "기다리고 있소.";
			    link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "나는 아직도 필요해: 철목 - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "좋아.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)* 0.35);
				}
				else
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
				}
			}
			else
			{
				
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.35 + sti(shTo.Bonus_Capacity));
				}
				else
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
				}
			}
	        shTo.Tuning.Capacity = true;

	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = "...이제 다 된 것 같소... 이제 창고를 완전히 실어도 되오, 내 일의 품질은 내가 보장하오.";
			Link.l1 = "고마워! 내가 시험해 볼게.";
			Link.l1.go = "Exit";
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar,  1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar,  2 );
			s2 = "Let's see what we can do, then. At the moment the speed of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);	
			s2 = s2 + " knots. In order to replace the sails I will require: sail silk - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
            dialog.Text = s2;
			Link.l1 = "좋소. 조건을 받아들이겠소. 필요한 건 뭐든 가져다주겠소.";
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = "아니. 그건 내 마음에 들지 않아.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
			
		case "ship_tunning_SpeedRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType   	= Pchar.Ship.Type;
			    NPChar.Tuning.ShipName   	= RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.text = "좋아. 재료를 기다리고 있겠어.";
				link.l1 = LinkRandPhrase("오래 기다릴 필요 없다고 장담하오. 이런 문제는 내가 바로 해결할 수 있소, 알겠소?","이미 그들을 데리고 있다고 생각하고, 나를 위해 부두를 잡아 둬. 나는 바람처럼 빨리 갈 테니까.","물론이지. 네가 부탁한 물건을 가진 몇 사람만 만나고 오면 돼, 하하!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the speed at " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". As the deposit was paid for " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "보증금을 못 봤는데...";
				link.l1 = "나중에 들르겠소.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "시간이 흐르고, 배는 기다리고 있소. 내가 부탁한 것들 모두 가져왔소?";
			    Link.l1 = "그래, 뭔가 찾아냈어.";
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
			    Link.l2 = "아니, 아직 진행 중이야.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("터","s")+", 우리가 약속했을 때 이후로 배를 바꾼 건가? 그러면 안 됐는데.";
			    Link.l1 = "아, 모든 게 상황 탓이지! 예치금이 날아가 버려서 안타깝군...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "좋아, 이제 필요한 건 다 모였군. 그럼 바로 작업 시작하지.";
			    link.l1 = "기다리고 있다.";
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "나는 아직도 필요한 게 있어: 선박용 비단 - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "좋아.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate) * 0.35);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.3 + stf(shTo.Bonus_SpeedRate);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
				}
			}
	        shTo.Tuning.SpeedRate = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... 모든 준비가 끝났습니다, 선장님. 돛을 모두 올리고 바람을 잡으십시오. 원하시면 직접 확인해 보셔도 됩니다!";
			Link.l1 = "고마워! 내가 시험해 볼게.";
			Link.l1.go = "Exit";			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			s2 = "Let's see what we can do, then. At the moment the maneurability of your ship is " + stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);			
			s2 = s2 + " In order to add new sails to shake it up I shall require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";										
            dialog.Text = s2;
			Link.l1 = "알겠소. 조건을 받아들이겠소. 필요한 건 뭐든 가져다주겠소.";
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = "아니. 그건 내 마음에 들지 않아.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_TurnRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.text = "좋아. 자재를 기다리고 있겠다.";
				link.l1 = LinkRandPhrase("오래 기다릴 일 없을 거라 장담하오. 이런 문제는 내가 바로 해결할 수 있소, 알겠소?","이미 가지고 있다고 생각하고 나를 위해 부두를 잡아 두시오. 나는 바람처럼 빠르게 올 테니.","물론이지. 네가 부탁한 물건을 가진 사람 몇 명만 만나고 오면 돼, 하하!");			    
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase agility by " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of  " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "보증금이 안 보이는데...";
				link.l1 = "나중에 들르겠소.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "시간이 흐르고, 배는 기다리고 있소. 내가 부탁한 것들 다 가져왔소?";
			    Link.l1 = "그래, 뭔가를 전달하는 데 성공했어.";
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
			    Link.l2 = "아니, 아직 진행 중이오.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("터","s")+", 우리가 약속했을 때 이후로 배를 바꾼 건가? 그러면 안 됐지.";
			    Link.l1 = "아, 이게 다 상황 때문이지! 보증금까지 날아가 버려서 안타깝군...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "좋아, 이제 필요한 건 다 모였군. 그럼 바로 작업 시작하지.";
			    link.l1 = "기다리고 있다.";
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "아직 필요한 게 있어: 밧줄 - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "좋소.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
			}
			else
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}	

	        shTo.Tuning.TurnRate = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4") && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
			dialog.Text = "... 이제 모든 준비가 끝났소... 지금 키를 점검해 보시오, 선장!";
			Link.l1 = "고마워! 내가 시험해 볼게.";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the maximum number of sailors in your crew, including overloading, is " + sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew) + " men.";			
			s2 = s2 + " I will require: ironwood - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "알겠소. 조건을 받아들이겠소. 필요한 건 뭐든 가져다주겠소.";
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = "아니. 그건 내 마음에 들지 않아.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MaxCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.text = "훌륭하군. 자재를 기다리고 있겠네.";
				link.l1 = LinkRandPhrase("오래 기다릴 일 없을 거라 장담하오. 이런 문제는 내가 바로 해결할 수 있소, 알겠소?","이미 가지고 있다고 생각하고, 나를 위해 부두를 잡아 두시오. 나는 바람처럼 빨리 올 테니.","물론이지. 네가 부탁한 물건을 가진 사람 몇 명만 만나면 되겠군, 하하!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For their efforts to increase the crew of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" shipwright requires: ironwood - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "보증금이 안 보이는데...";
				link.l1 = "나중에 들르겠소.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "시간이 흐르고, 배는 기다리고 있소. 내가 부탁한 것들 모두 가져왔소?";
			    Link.l1 = "그래, 뭔가 찾아냈어.";
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
			    Link.l2 = "아니, 아직 작업 중이오.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("테르","s")+", 우리가 약속했을 때 이후로 배를 바꾼 건가? 그러면 안 됐는데.";
			    Link.l1 = "아, 이게 다 상황 때문이지! 예치금이 날아가 버려서 아쉽군...";				
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "좋아, 이제 필요한 건 다 모였군. 그럼 바로 작업 시작하지.";
			    link.l1 = "기다리고 있다.";
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "아직도 필요한 게 있어: 철목 - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "좋아.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ironwood - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew) * 0.35);
			}
			else
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
			}
	        shTo.Tuning.MaxCrew = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... 끝났습니다, 선장님. 이제 선원을 더 고용하실 수 있습니다. 모두가 탈 공간이 충분할 것입니다.";
			Link.l1 = "고마워! 내가 시험해 볼게.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

		
		////////////////////////////////////////// MinCrew ////////////////////////////////////////////////////
		case "ship_tunning_MinCrew":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Let's see what we can do, then. At the moment the minimum number of required sailors in your crew is " + sti(RealShips[sti(Pchar.Ship.Type)].MinCrew) + " men.";			
			s2 = s2 + " To improve the controllability of the ship and to reduce the required number of sailors in the crew I will require: ropes - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "알겠소. 조건을 받아들이겠소. 필요한 건 뭐든 가져다주겠소.";
			Link.l1.go = "ship_tunning_MinCrew_start";
			Link.l2 = "아니. 그건 내 마음에 들지 않아.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MinCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
                dialog.text = "훌륭하군. 자재를 기다리고 있겠네.";
				link.l1 = LinkRandPhrase("오래 기다릴 일 없을 거라 장담하오. 이런 문제쯤은 내가 바로 해결할 수 있소, 알겠소?","이미 그들을 데리고 있다고 생각하고, 나를 위해 부두를 잡아 두시오. 나는 바람처럼 빠르게 올 것이오.","물론이지. 네가 부탁한 물건을 가진 몇 사람만 만나고 오면 돼, 하하!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to reduce the minimum required number of crew on " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ropes - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "보증금이 안 보이는데...";
				link.l1 = "나중에 들르겠소.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MinCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "시간이 흐르고, 배는 기다리고 있소. 내가 부탁한 것들 모두 가져왔소?";
			    Link.l1 = "그래, 뭔가 찾아냈어.";
			    Link.l1.go = "ship_tunning_MinCrew_again_2";
			    Link.l2 = "아니, 아직 진행 중이야.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("테르","s")+", 우리가 약속한 이후로 배를 바꾼 건가? 그러면 안 됐는데.";
			    Link.l1 = "아, 모든 게 상황 때문이지! 보증금이 날아가 버려서 아쉽군...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MinCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "좋아, 이제 필요한 건 다 모였군. 그럼 바로 작업 시작하지.";
			    link.l1 = "기다리고 있다.";
			    link.l1.go = "ship_tunning_MinCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "아직 필요한 게 있어: 밧줄 - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "좋아.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ropes - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MinCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew) * 0.35);
			}
			else
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
			}
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
	        shTo.Tuning.MinCrew = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4")  && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... 준비됐습니다, 선장님! 이제 더 적은 수의 선원으로도 똑같은 결과로 배를 조종할 수 있습니다.";
			Link.l1 = "고마워! 내가 시험해 볼게.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what we can do, then. At the moment the ship's hull is " + sti(RealShips[sti(Pchar.Ship.Type)].HP);			
			s2 = s2 + ". To reinforce the hull, I will require: resin - "+ Material + ".";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "알겠소. 조건을 받아들이겠소. 필요한 건 뭐든 가져다주겠소.";
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = "아니. 그건 내 마음에 들지 않아.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_HP_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.text = "좋아. 자재를 기다리고 있겠다.";
				link.l1 = LinkRandPhrase("오래 기다릴 일은 없을 거라고 장담하오. 이런 문제는 내가 바로 해결할 수 있소, 알겠소?","이미 그들을 데리고 있다고 생각하고, 나를 위해 부두를 잡아 둬. 나는 바람처럼 빠르게 갈 테니.","물론이지. 네가 부탁한 물건을 가진 사람 몇 명만 찾아가면 되겠군, 하하!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his efforts to increase the strength of the hull " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "보증금이 안 보이는데...";
				link.l1 = "나중에 들르겠소.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "시간이 흐르고, 배는 기다리고 있소. 내가 부탁한 것들 다 가져왔소?";
			    Link.l1 = "그래, 뭔가 찾아냈어.";
			    Link.l1.go = "ship_tunning_HP_again_2";
			    Link.l2 = "아니, 아직 작업 중이오.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("터","s")+", 우리가 약속한 이후로 배를 바꾼 건가? 그러면 안 됐는데.";
			    Link.l1 = "아, 이게 다 상황 때문이지! 예치금이 날아가 버려서 아쉽군...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_OIL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "좋아, 이제 필요한 건 다 모였군. 그럼 바로 작업 시작하지.";
			    link.l1 = "기다리고 있다.";
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "아직 필요한 것: 송진 - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "좋아.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_HP"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP) * 0.35);
				}
				else
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					if(sti(shTo.HP) > sti(shTo.Bonus_HP)) // иначе апгрейд будет умножать отрицательное значение
					{
						shTo.HP    = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.35 + sti(shTo.Bonus_HP));
					}
				}
				else
				{
					if(sti(shTo.HP) > sti(shTo.Bonus_HP)) // иначе апгрейд будет умножать отрицательное значение
					{
						shTo.HP    = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
					}
				}
			}
	        shTo.Tuning.HP = true;
			ProcessHullRepair(pchar, 100.0); // у нпс при апгрейде есть, здесь тоже должно быть

			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
			TuningAvailable();
            NextDiag.TempNode = "First time";
			
			dialog.Text = "... 이제 됐소... 이제부터는 적들이 당신 배의 선체를 부수기가 훨씬 더 어려울 거라고 내가 보장하오!";
			Link.l1 = "헤헤, 네 말을 믿지! 고맙다, 주인장.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_REPAIR, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			fTmp = 180.0 - (acos(1 - stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed)) * 180.0/PI);
			s2 = "Let's see what we can do, then. At the moment the point of sail by the wind is " + makeint(fTmp) + " degrees.";
			// belamour legendary edition если спускать курс по ветру, то это даунгрейд
			s2 = s2 + " To accelerate the ship upwind, I will require: ship silk - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";									
            dialog.Text = s2;
			Link.l1 = "알겠소. 조건을 받아들이겠소. 필요한 건 뭐든 가져다주겠소.";
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = "아니. 그건 내 마음에 들지 않아.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;

		case "ship_tunning_WindAgainst_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial    	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.text = "좋아. 재료를 기다리고 있겠다.";
				link.l1 = LinkRandPhrase("오래 기다릴 필요 없다고 장담하오. 이런 문제는 내가 바로 해결할 수 있소, 알겠소?","이미 받은 셈 치고, 나를 위해 부두를 잡아 두시오. 나는 바람처럼 빠르게 올 테니.","물론이지. 네가 부탁한 물건을 가진 사람 몇 명만 만나고 오면 돼, 하하!");
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work on changing the wind angle of " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" shipwright requires: ship silk - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "보증금이 안 보이는데...";
				link.l1 = "나중에 들르겠소.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			    dialog.Text = "시간이 흐르고, 배는 기다리고 있소. 내가 부탁한 것들 모두 가져왔소?";
			    Link.l1 = "그래, 뭔가 전하는 데 성공했어.";
			    Link.l1.go = "ship_tunning_WindAgainst_again_2";
			    Link.l2 = "아니, 아직 작업 중이오.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("터","s")+", 우리가 약속한 이후로 배를 바꾼 건가? 그러면 안 됐는데.";
			    Link.l1 = "아, 모든 게 상황 탓이지! 보증금이 날아가 버려서 아쉽군...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "좋아, 이제 필요한 건 다 모였군. 그럼 바로 작업 시작하지.";
			    link.l1 = "기다리고 있소.";
			    link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.Text = "나는 아직도 필요해: 배의 비단 - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "좋소.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: ship silk - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;

		case "ship_tunning_WindAgainst_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим			
			// belamour legendary edtion чем больше WindAgainstSpeed, тем круче к ветру
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.35 * stf(shTo.WindAgainstSpeed);	
			}
			else
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.20 * stf(shTo.WindAgainstSpeed);
			}
			if (stf(shTo.WindAgainstSpeed) > 1.985) shTo.WindAgainstSpeed = 1.985;
	        shTo.Tuning.WindAgainst = true;

			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... 준비됐습니다, 선장님!.. 이제 당신 배가 바람을 거슬러 훨씬 더 빠르게 나아갈 겁니다.";
			Link.l1 = "고마워! 내가 시험해 볼게.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
						
		////////////////////////////////////////// только количество орудий  ////////////////////////////////////////////////////	
		case "ship_c_quantity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Let's see what can be done there. Right now, the number of cannons on your ship is " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity) + ", and the maximum possible number is - " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax) + ".";			
			s2 = s2 + " I can tell you right away that it's not going to be cheap. I will require: resin - "+ Material + ",";
			s2 = s2 + " As payment for my work I will take: " + WorkPrice + " chests of doubloons - to cover my expenses. That should be all. Oh, and cash up front.";						
			dialog.Text = s2;		
			Link.l1 = "알겠소. 조건을 받아들이겠소. 필요한 건 뭐든 가져오겠소.";
			Link.l1.go = "ship_c_quantity_start";		
			Link.l2 = "아니. 그건 내 마음에 들지 않아.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_c_quantity_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("Chests of doubloons were taken from the cabin: " + iSumm+ " pcs.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Cannon 		= true;				
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 				
				NPChar.Tuning.ShipType      = Pchar.Ship.Type;
				NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;											    
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.text = "좋아. 자재를 기다리고 있겠다.";
				link.l1 = LinkRandPhrase("오래 기다릴 일 없을 거라 장담하오. 이런 문제는 내가 바로 해결할 수 있소, 알겠소?","이미 그들을 데리고 있다고 생각하고 나를 위해 부두를 잡아 둬. 나는 바람처럼 빨리 갈 테니.","물론이지. 네가 부탁한 물건을 가진 몇 사람만 만나고 오면 되겠군, 하하!");
				link.l1.go = "Exit";			    
				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "For his work to increase the number of cannons on the " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +						
				" shipwright requires: resin - " + NPChar.Tuning.Matherial + ". A deposit was paid in front in the amount of " + NPChar.Tuning.Money + " chests of doubloons.");				
			}		
			else
			{ 
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "입금이 안 보이는데...";
				link.l1 = "나중에 들르겠소.";
				link.l1.go = "Exit";
			}
		break;		
		
		case "ship_c_quantity_again":	
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "시간이 흐르고, 배는 기다리고 있소. 내가 부탁한 것들 다 가져왔소?";
				Link.l1 = "그래, 뭔가 찾아냈어.";
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = "아니, 아직 작업 중이오.";
				Link.l2.go = "Exit";
			}		
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+GetSexPhrase("ter","s")+", 우리가 약속했을 때 이후로 배를 바꾼 건가? 그러면 안 됐는데.";
			    Link.l1 = "아, 모든 게 상황 탓이지! 보증금이 날아가 버려서 아쉽군...";
				Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
				AddQuestRecord("ShipTuning", "Lose");
				CloseQuestHeader("ShipTuning");
			}		
		break;
		
		case "ship_c_quantity_again_2":		
			checkMatherial(Pchar, NPChar, GOOD_OIL);
			if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.text = "좋아, 이제 필요한 건 다 모였군. 그럼 바로 작업 시작하지.";
				link.l1 = "기다리고 있다.";
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "나는 아직도 필요해: 송진 - "+sti(NPChar.Tuning.Matherial)+".";
				link.l1 = "좋아.";
				link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "I need to bring: resin - "+ sti(NPChar.Tuning.Matherial) + ".");
			}		
		break;
		
		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");		
			makearef(refShip, pchar.Ship);
			
			iCannonDiff = sti(refShip.CannonDiff);
			iCannonDiff -= 1;
								
			for (i = 0; i < sti(shTo.cannonr); i++)
			{
				attr = "c" + i;										
					
				if(i < (sti(shTo.cannonr) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0; 
					}	
				}					
			}	
			for (i = 0; i < sti(shTo.cannonl); i++)
			{
				attr = "c" + i;
				if(i < (sti(shTo.cannonl) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0; 
					}	
				}										
			}	
			
			if(CheckAttribute(shTo,"CannonsQuantityMax")) 	shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
			else										    shTo.Cannons = sti(shTo.CannonsQuantity) - iCannonDiff * 2;
			
			shTo.CannonsQuantity = sti(shTo.Cannons);
		
			refShip.Cannons = sti(shTo.Cannons);
			refShip.CannonDiff = iCannonDiff;			

			shTo.Tuning.Cannon = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			NextDiag.TempNode = "First time";
			dialog.Text = "... 그게 다요, 선장님. 추가 대포를 쓸 수 있소 — 물론 가지고 있다면 말이오, 헤헤.";
			Link.l1 = "고맙다!";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("You have learned a lot about the structure of this ship!", "none");
			AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_CANNONS, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		case "Tasks":
			//--> Jason генератор Поиск корабля
			if (hrand(4) == 2 && !CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && sti(pchar.rank) < 19)
			{
				if (!CheckAttribute(npchar, "Findship") || GetNpcQuestPastDayParam(npchar, "Findship") >= 60) 
				{
					SelectFindship_ShipType(); //выбор типа корабля
					pchar.GenQuest.Findship.Shipyarder.ShipBaseName =  GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Findship.Shipyarder.ShipType), "Name") + "Acc")); // new
					pchar.GenQuest.Findship.Shipyarder.City = npchar.city; //город квестодателя
					dialog.text = "해결해야 할 일이 있소. 배를 주문하려고 하는데 - "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+". 하지만 지금 내 조선소에는 그런 배가 없고, 앞으로 두 달 안에도 구할 방법이 없소.\n만약 그런 배를 가져다줄 수 있다면 정말 감사하겠고, 판매가의 1.5배를 지불하겠소.";
					link.l1 = "흥미로운 제안이군. 동의하지!";
					link.l1.go = "Findship";
					link.l2 = "이건 내 관심 밖이야.";
					link.l2.go = "Findship_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Findship");
					break;
				}
				
			}//<-- генератор Поиск корабля
			//Jason --> генератор Неудачливый вор
			if (hrand(6) == 1 && !CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && sti(pchar.rank) < 10 && npchar.city != "Charles")
			{
				if (!CheckAttribute(npchar, "Device")) 
				{
					switch (hrand(4))
					{
						case 0:  
							pchar.GenQuest.Device.Shipyarder.Type = "inside gage";
							pchar.GenQuest.Device.Shipyarder.Describe = "two hammered strips, connected with a joint unriveted on both ends";
						break; 
						case 1:  
							pchar.GenQuest.Device.Shipyarder.Type = "Swedish broad axe";
							pchar.GenQuest.Device.Shipyarder.Describe = "an axe on a long straight handle with a thin semicircular blade";
						break; 
						case 2:  
							pchar.GenQuest.Device.Shipyarder.Type = "groover";
							pchar.GenQuest.Device.Shipyarder.Describe = "a small axe, looking like a farmer's mattock";
						break; 
						case 3:  
							pchar.GenQuest.Device.Shipyarder.Type = "stockpile level";
							pchar.GenQuest.Device.Shipyarder.Describe = "two wooden bars of equal length, linked by the same third one, which has in the middle a rotating liquid-filled plate with an air bubble";
						break;
						case 4:  
							pchar.GenQuest.Device.Shipyarder.Type = "barsik";
							pchar.GenQuest.Device.Shipyarder.Describe = "an ordinary flail, but the chain is rod-shaped and only moves in one direction";
						break; 
					}
					dialog.text = "딱 맞춰 오셨군. 혹시 나 좀 도와줄 수 있겠나. 어제 누가 내 아주 귀중한 도구를 훔쳐 갔거든 - "+pchar.GenQuest.Device.Shipyarder.Type+". 나는 또 하나를 만들 여유도 없고, 유럽에서 주문할 시간이나 돈도 없어. 그리고 그게 없으면 제대로 배를 지을 수가 없지, 알겠나?\n가장 짜증나는 건 이 물건이 조선공 말고는 아무도 필요 없다는 거야, 그리고 이 식민지에서 조선공은 나 하나뿐이지. 그 도둑놈은 이걸 누구한테도 팔 수 없으니 그냥 버려버릴 거야. 혹시 도둑을 쫓아가서 마을 사람들에게 물어볼 수 있겠나? 나는 조선소를 떠날 시간이 없어 – 급하게 완성해야 할 특별 주문이 있거든.";
					link.l1 = "좋아, 한번 해보지. 말해 봐, 그... 네 장치가 어떻게 생겼었지?";
					link.l1.go = "Device";
					link.l2 = "이건 내 관심 밖이야.";
					link.l2.go = "Device_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Device");
					break;
				}//<-- генератор Неудачливый вор
			}
			dialog.text = "그런 건 아무것도 없어.";
			link.l1 = "말씀대로 하겠습니다.";
			link.l1.go = "exit";
		break;
		
		case "Findship_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		
		case "Device_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		
		//--> Jason генератор Поиск корабля
		case "Findship":
			pchar.GenQuest.Findship.Shipyarder = "begin";
			pchar.GenQuest.Findship.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Findship.Shipyarder.City = npchar.city;
			ReOpenQuestHeader("Findship");
			AddQuestRecord("Findship", "1");
			AddQuestUserData("Findship", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Findship.Shipyarder.City+"Gen"));
			AddQuestUserData("Findship", "sName", pchar.GenQuest.Findship.Shipyarder.Name);
			AddQuestUserData("Findship", "sShip", pchar.GenQuest.Findship.Shipyarder.ShipBaseName);
			SetFunctionTimerCondition("Findship_Over", 0, 0, 60, false);
			DialogExit();
		break;
		
		case "Findship_check":
			dialog.text = "훌륭하군! 이렇게 빨리 해내다니 정말 기쁘네. 그 배는 어디 있지?";
			link.l1 = "지금 그 배는 정박지에 있어; 이름은 '"+pchar.GenQuest.Findship.Shipyarder.ShipName+"'.";
				link.l1.go = "Findship_complete";
				break;
		
		case "Findship_complete":
			pchar.quest.Findship_Over.over = "yes";//снять прерывание
			sld = GetCharacter(sti(pchar.GenQuest.Findship.Shipyarder.CompanionIndex));
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			dialog.text = "여기 돈이오 - "+FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money))+". 일 맡겨줘서 고맙소. 또 들르기를 잊지 마시오. 안녕히 가시오!";
			link.l1 = "안녕히 가십시오, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Findship.Shipyarder.Money));
			AddQuestRecord("Findship", "3");
			AddQuestUserData("Findship", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)));
			CloseQuestHeader("Findship");
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		//<-- генератор Поиск корабля
		
		//Jason --> генератор Неудачливый вор
		case "Device":
			pchar.GenQuest.Device.Shipyarder.Chance1 = rand(6);
			pchar.GenQuest.Device.Shipyarder.Chance2 = rand(3);
			pchar.GenQuest.Device.Shipyarder.Chance3 = rand(2);
			pchar.GenQuest.Device.Shipyarder.Chance4 = rand(4);
			pchar.GenQuest.Device.Shipyarder.Money = 12000+rand(8000);
			//генерируем тип корабля для бонуса сейчас, чтобы не сливали
			if (sti(pchar.rank) < 5) iType = sti(RandPhraseSimple(its(SHIP_BARKENTINE), its(SHIP_SLOOP)));
			if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 11) iType = sti(RandPhraseSimple(its(SHIP_SHNYAVA), its(SHIP_BARQUE)));
			if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 16) iType = sti(RandPhraseSimple(its(SHIP_BRIG), its(SHIP_FLEUT)));
			if (sti(pchar.rank) >= 16) iType = sti(LinkRandPhrase(its(SHIP_CORVETTE), its(SHIP_POLACRE), its(SHIP_GALEON_L)));
			pchar.GenQuest.Device.Shipyarder.Bonus = iType;
			dialog.text = "물론이오, 최대한 쉽게 설명해 보겠소. 보아하니\n "+pchar.GenQuest.Device.Shipyarder.Describe+". 그건 세상에 하나뿐인 물건이라 아주 쉽게 알아볼 수 있을 거요. 그 악기를 나에게 가져오면 후하게 보상하겠소.";
			link.l1 = "알겠습니다. 바로 수색을 시작하겠습니다!";
			link.l1.go = "exit";
			pchar.GenQuest.Device.Shipyarder = "begin";
			pchar.GenQuest.Device.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Device.Shipyarder.City = npchar.city;
			pchar.GenQuest.Device.Shipyarder.Nation = npchar.Nation;
			ReOpenQuestHeader("Device");
			AddQuestRecord("Device", "1");
			AddQuestUserData("Device", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Device.Shipyarder.City+"Voc"));
			AddQuestUserData("Device", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			AddQuestUserData("Device", "sDesc", pchar.GenQuest.Device.Shipyarder.Describe);
			SetFunctionTimerCondition("Device_Over", 0, 0, 30, false);
		break;
		
		case "Device_complete":
			pchar.quest.Device_Over.over = "yes";//снять прерывание
			dialog.text = "해냈군! 내가 얼마나 고마운지 모를 거야! 내 악기를 다시 볼 희망은 이미 다 버렸었지.";
			link.l1 = "여기 있다.";
			link.l1.go = "Device_complete_1";
		break;
		
		case "Device_complete_1":
			RemoveItems(PChar, "Tool", 1);
			dialog.text = "수고에 대한 보수를 주겠소 "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money))+". 그게 적절한 보상이 되길 바라오.";
			link.l1 = "고마워!";
			link.l1.go = "Device_complete_2";
		break;
		
		case "Device_complete_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Device.Shipyarder.Money));
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddQuestRecord("Device", "10");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)));
			CloseQuestHeader("Device");
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance4) == 3)
			{
				dialog.text = "게다가, 감사의 표시로 제안을 하나 더 드리고 싶소.";
				link.l1 = "재미있군. 좋아, 해봐라 - 나는 기분 좋은 놀람을 좋아하니까.";
				link.l1.go = "Device_complete_3";
			}
			else
			{
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
		break;
		
		case "Device_complete_3":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			dialog.text = "방금 새 배를 진수했어 - "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(iType,"Name")+"Acc"))+". 이미 이 배에 관심 있는 손님들이 몇 명 있지만, 우선권을 드리겠소. 이 배가 마음에 들고 가격이 두렵지 않다면, 구입할 수 있소.";
			link.l1 = "헤헤! 그래, 한번 보자!";
			link.l1.go = "Device_complete_4";
			link.l2 = "고맙소만, 지금 내 배가 딱 마음에 들어서 바꿀 생각은 없소.";
			link.l2.go = "Device_complete_5";
		break;
		
		case "Device_complete_4":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(iType, NPChar), "ship10");
			DialogExit();
			LaunchShipyard(npchar);
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // лесник , митрокоста		   
		break;
		
		case "Device_complete_5":
			dialog.text = "원하시는 대로 하십시오. 다시 한 번 감사드리오 - 행운을 빕니다!";
			link.l1 = "너에게도 행운이 있길 바란다!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		// <-- генератор Неудачливый вор
		
		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "잠깐만 봐주겠소... 아니, 그런 사람은 없었소. 그 일이라면 항만 관리자에게 가보는 게 좋겠구려.";
				link.l1 = "물론이지...";
				link.l1.go = "exit";
			}
			else
			{
				sTemp = "Let me take a look, Captain! A-ha! Those are the ship documents of a good friend of mine, my favorite customer! I am sure he will be extremely happy because of your find and will reward you deservedly.";
				sTemp = sTemp + "I guess I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " pesos on his behalf";
				dialog.text = sTemp;
				link.l1 = "아니, 그렇게 생각하지 않아...";
				link.l1.go = "exit";
				link.l2 = "감사합니다, "+GetFullName(NPChar)+"! 당신 친구에게 내 안부를 전해 주시오.";
				link.l2.go = "ShipLetters_7";				
			}	
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "4");		
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "잘 듣고 있소.";
			link.l1 = "도망자를 데려왔어.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "아이고, 선장님, 정말 감사합니다! 그 아가씨는 괜찮습니까? 다친 데는 없습니까? 왜 도망친 겁니까? 왜죠?\n그 아가씨는 모르는 겁니까? 신랑은 부유하고 중요한 사람입니다! 젊음이란 순진하고 어리석지요... 심지어 잔인하기도 합니다. 그것을 명심하십시오!";
			link.l1 = "음, 당신이 그녀의 아버지이고 최종 결정은 당신에게 달려 있지만, 결혼을 서두르지는 마십시오...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "네가 뭘 안다고 그래? 자식이라도 있나? 없어? 나중에 자식 생기면 나한테 와서 얘기해 보자고.\n그 애를 가족에게 데려오는 사람에게는 내가 상을 주겠다고 약속했지.";
			link.l1 = "고마워. 그녀를 계속 지켜보는 게 좋겠어. 내 촉으로는 저걸로 끝나지 않을 것 같거든.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;		
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "오, 그럼 내 방탕한 아들에게 어린 신부를 데려온 선장이 바로 당신이오?";
				link.l1 = "그래, 나였어.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "오, 거기 "+GetSexPhrase("그는 우리 은인이야","그렇소, 우리 은인이오\n")+". 보상을 기대하고 있는 건가?";
				link.l1 = "보상은 없어도 괜찮소, 좋은 말씀 한마디면 충분하오.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "제 아이가 궁지에 몰렸을 때 버리지 않고, 난처한 상황에서 벗어날 수 있도록 도와주셔서 진심으로 감사드립니다.\n감사의 뜻을 전하고 싶으니, 부디 이 작은 금액과 제 선물을 받아주십시오.";
			link.l1 = "감사합니다. 이 젊은 부부를 도울 수 있어 기뻤습니다.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "고맙다고? 무슨 고마움?! 저 멍청이가 벌써 반년째 빈둥거리며 일도 안 하고 돌아다니고 있잖아 - 그런데 연애할 시간은 또 넉넉하군! 내가 저 나이였을 땐 이미 내 사업을 하고 있었지! 푸! 총독에게는 혼기가 찬 딸이 있는데, 저 바보 녀석은 집안도 없는 계집애를 내 집에 데려와서는 감히 내 축복을 달라고 하다니!";
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
			dialog.text = "무슨 감정? 어떤 감정을 말하는 거냐? 감정이라니... 네 나이에 그렇게 생각 없이 굴 수가 있나?! 어린 것들 비위 맞추고 뒷일 봐주는 네 꼴이 부끄럽지도 않냐! 네가 한 짓은 그저 처녀를 집에서 데려간 것만이 아니라, 내 풋내기의 인생까지 망쳐 놓은 거다. 너한테 고마울 일은 하나도 없다. 이만 가거라.";
			link.l1 = "좋아, 너도 마찬가지로...";
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
		
		case "shipyard":
			if(CheckAttribute(npchar, "TrialDelQuestMark"))
			{
				DeleteAttribute(npchar, "TrialDelQuestMark");
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("PortRoyal");
			}
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("장난하는 거야? 네 배가 어디 있는데? 항구에 안 보이잖아!","악마에게 맹세코, 너한테 속지 않아! 네 배는 항구에 없어!"),pcharrepphrase("항구에 당신 배가 보이지 않는데요, 선장님 "+GetFullName(pchar)+". 그 배가 '플라잉 더치맨'이 아니길 바란다네?","선장님, 부두에서 화물을 싣는 게 훨씬 쉽습니다. 배를 항구에 대고 다시 오십시오."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"귀찮게 됐군! 좋아, 이 늙은 여우야, 곧 보자고!","당신을 속이고 싶지 않았소, "+GetFullName(npchar)+", 섬 반대편에 있는 배요."),pcharrepphrase("아니. 내 배 이름은 '블랙 펄'이야! 얼굴이 왜 그래? 창백하잖아... 하하! 그냥 농담이야!","조언 고마워, 꼭 그렇게 할게."));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("농담하는 거야? 네 배는 어디 있지? 항구에 안 보이는데!","악마에게 맹세코, 너한테 속지 않을 거다! 네 배는 항구에 없어!"),pcharrepphrase("항구에 당신 배가 안 보이는데요, 선장님 "+GetFullName(pchar)+". 혹시 그 배가 '플라잉 더치맨'은 아니겠지?","선장님, 부두에서 화물을 싣는 게 훨씬 쉽습니다. 배를 항구로 들여오고 다시 오십시오."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"귀찮게 됐군! 좋아, 이 늙은 여우야, 곧 보자고!","당신을 속이고 싶지 않았소, "+GetFullName(npchar)+", 섬 반대편에 배가 있어."),pcharrepphrase("아니. 내 배 이름은 '블랙 펄'이야! 얼굴이 왜 그래? 창백하잖아... 하하! 그냥 농담이야!","조언 고맙소, 꼭 그렇게 하겠소."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsGerald":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    dialog.text = "돛 색깔을 바꾸는 데 드는 비용은 "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSCOLOR_PRICE_RATE))+", 문장을 변경하는 데 드는 비용은 "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSGERALD_PRICE_RATE))+", 돛을 교체하는 건 네 배에 따라 달라진다.";
							  
			    link.l1 = "새로운 색을 선택하시오.";
			    link.l1.go = "SailsColorChoose";
			    link.l2 = "새로운 문장을 그려 주시오.";
			    link.l2.go = "SailsGeraldChoose";
				link.l3 = "특별한 돛을 설치해."; 
				link.l3.go = "SailsTypeChoose";
			    Link.l9 = "내 마음이 바뀌었어.";
				Link.l9.go = "exit";
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("장난하는 거야? 네 배는 어디 있지? 항구에 안 보이는데!","악마에게 맹세코, 너한테 속지 않아! 네 배는 항구에 없어!"),pcharrepphrase("항구에 당신 배가 안 보이는데요, 선장님 "+GetFullName(pchar)+". 그녀가 '플라잉 더치맨'은 아니길 바라오?","선장님, 부두에서 화물을 싣는 게 훨씬 쉽습니다. 배를 항구로 대고 다시 오십시오."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"귀찮게 하네! 좋아, 이 늙은 여우야, 곧 보자!","널 속이고 싶진 않았어, "+GetFullName(npchar)+", 섬 건너편에 있는 배다."),pcharrepphrase("아니. 내 배 이름은 '블랙 펄'이야! 네 얼굴에 무슨 일 있었냐? 창백하네... 하하! 그냥 농담이야!","조언 고마워, 꼭 그렇게 할게."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsTypeChoose":
			dialog.text = "어떤 돛을 설치하시겠습니까? 현재 가지고 계신 것은\n "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+".";
            Link.l6 = "설치하고 싶어 "+GetSailsType(6)+".";
			Link.l6.go = "SailsTypeChooseIDX_6";
			Link.l7 = "설치하고 싶어 "+GetSailsType(7)+".";
			Link.l7.go = "SailsTypeChooseIDX_7";
			Link.l8 = "설치하고 싶어 "+GetSailsType(8)+".";
			Link.l8.go = "SailsTypeChooseIDX_8";
			Link.l9 = "설치하고 싶어 "+GetSailsType(9)+".";
			Link.l9.go = "SailsTypeChooseIDX_9";
			Link.l10 = "설치하고 싶어 "+GetSailsType(10)+".";
			Link.l10.go = "SailsTypeChooseIDX_10";
			Link.l11 = "설치하고 싶어 "+GetSailsType(11)+".";
			Link.l11.go = "SailsTypeChooseIDX_11";
			attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
			DeleteAttribute(Link, attrLoc);
		    Link.l99 = "생각이 바뀌었어.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChoose2":
            NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
			                                          sti(NPChar.SailsTypeChooseIDX),
													  stf(NPChar.ShipCostRate),
													  sti(RealShips[sti(Pchar.Ship.Type)].Price));
													  
			dialog.text = "현재 당신은 가지고 있소\n "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+", 선택하셨습니다 "+GetSailsType(sti(NPChar.SailsTypeChooseIDX))+". 교체 비용은 "+FindRussianMoneyString(sti(NPChar.SailsTypeMoney))+". 진행하시겠습니까?";

			if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
			{
	            Link.l1 = "그래.";
				Link.l1.go = "SailsTypeChooseDone";
			}
		    Link.l99 = "아니.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChooseDone":
			AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
			dialog.text = "좋아! 모든 게 잘 될 거야.";
		    Link.l9 = "고맙소.";
			Link.l9.go = "exit";

			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsColorChoose":
			if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
			{
				dialog.text = "어떤 색으로 할까? 가격은 "+FindRussianMoneyString(GetSailsTuningPrice(Pchar,npchar,SAILSCOLOR_PRICE_RATE))+".";
				for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
				{
					if (CheckSailsColor(Pchar, i))
					{
						attrLoc = "l" + i;
						Link.(attrLoc) = XI_ConvertString(SailsColors[i].name);
						Link.(attrLoc).go = "SailsColorIdx_" + i;
					}
				}
			    Link.l99 = "내 마음이 바뀌었어.";
				Link.l99.go = "exit";
			}
			else
			{
				dialog.text = "돈을 마련하면 다시 오시오.";
			    Link.l9 = "좋아.";
				Link.l9.go = "exit";	
			}
		break;
		
		case "SailsColorDone":
			AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
			dialog.text = "알겠소. 우리가 돛을 칠하겠소\n "+GetStrSmallRegister(XI_ConvertString(SailsColors[sti(NPChar.SailsColorIdx)].name))+" 색.";
		    Link.l9 = "고맙소.";
			Link.l9.go = "exit";
			
			SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsGeraldChoose":
			if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
			{
				if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchSailsGeraldScreen(npchar);
				}
				else
				{
				    dialog.text = "안타깝게도, 당신의 배는 문장을 달 수 없어.";
				    Link.l9 = "안됐군.";
					Link.l9.go = "exit";
				}
			}
			else
			{
				dialog.text = "돈을 가지고 오면 다시 오시오.";
			    Link.l9 = "좋소.";
				Link.l9.go = "exit";	
			}
		break;

//--> -------------------------------------------Бремя гасконца---------------------------------------------------
		case "Sharlie":
			dialog.text = "실망시켜 드려 죄송합니다, 나리. 하지만 지금은 판매할 배가 없습니다.";
			link.l1 = "그거 정말 이상하군, 내가 듣기로는 너희 조선소에 새로 만든 루거선이 있다고 하던데.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
			{
				dialog.text = "있지, 아마 미셸 드 몽페르가 삼천 페소 보증금을 걸었던 루거에 관한 얘기겠지? 그 배는 이미 팔렸어. 계약서에 따르면, 배가 진수된 후 일주일 이내에 전액을 지불해야 했거든.\n기한은 모두 지났고, 나는 돈을 받지 못했으니 루거는 팔려버렸지. 미안하네, 나리.";
				link.l1 = "그래, 정말 운이 없었지... 그런데 혹시 다른 배는 진짜로 안 파는 거야?";
				link.l1.go = "Sharlie_6";
			}
			else
			{
			dialog.text = "흠. 그렇지. 하지만...";
			link.l1 = "그리고 이미 선금이 들어와 있소 - 오천 페소지. 돈을 맡긴 미셸 드 몽페르가 이 배에 대한 모든 권리를 내게 넘겼소.";
			link.l1.go = "Sharlie_2";
			}
		break;
		
		case "Sharlie_2":
			int iDay = 3-sti(GetQuestPastDayParam("questTemp.Sharlie_ship"));
			sTemp = "You only have "+FindRussianDaysString(iDay)+"";
			if (iDay == 0) sTemp = "Today is the last day";
			dialog.text = "그렇다면 계속 이야기합시다, 나리. 말씀하신 대로, 저는 이미 배에 대한 오천 페소의 계약금을 받았습니다. 하지만 배의 전체 가치, 탄약까지 포함해서, 만오천 페소라고 생각합니다. 그러니 만 페소를 더 주시면 배는 당신 것이오.\n계약에 따르면, 배가 진수된 후 일주일 이내에 돈을 지불해야 합니다."+sTemp+", 그리고 나면 나는 이 배를 다른 손님에게 팔 수 있지. 참고로, 이미 한 명이 기다리고 있으니 서두르는 게 좋을 거야.";
			if (sti(Pchar.money) >= 10000)
			{
				link.l1 = "서두를 필요 없어. 지금 당장 필요한 금액을 가지고 있지. 자, 여기 있다.";
				link.l1.go = "Sharlie_4";
			}
			link.l2 = "좋소, 좋소. 돈은 곧 드리겠소, 나리. 오래 기다리게 하진 않겠소.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
			{
				dialog.text = "무엇을 도와드릴까요, 나리?";
				Link.l1 = "그냥 들러서 어떤 배들이 있는지 좀 보려고 했어... 하지만 지금은 좀 바빠. 처리해야 할 일이 남아 있거든. 그 일만 끝나면 바로 다시 올게.";
				Link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
			{	
				if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
				{
					dialog.text = "나리, 내가 분명히 사흘만 시간이 있다고 경고했소. 그 시간이 다 지났고, 돈도 가져오지 않았으니 우리 거래는 끝났소. 그래서 나는 그 배를 다른 손님에게 팔았소. 기분 나쁘게 생각하지 마시오.";
					link.l1 = "그래, 정말 운이 없었지... 그런데 혹시 다른 배는 정말로 안 파는 거야?";
					link.l1.go = "Sharlie_6";
				}
				else
				{
					dialog.text = "만 냥 가져왔소, 나리?";
					if (sti(Pchar.money) >= 10000)
					{
						link.l1 = "당연히 있지. 여기 있다.";
						link.l1.go = "Sharlie_4";
					}
					link.l2 = "아니, 아직 작업 중이야.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Sharlie_3";
				}
			}
		break;
		
		case "Sharlie_4":
			AddMoneyToCharacter(pchar, -10000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "그럼 이 성공적인 구매를 축하드리오. 이제 그 배는 당신 것이오. 잘 써먹길 바라오.";
			link.l1 = "고마워!";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "lugger";
			pchar.questTemp.Sharlie = "crew";
			//стартовый люггер
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_LUGGER, 6, 800, 40, 610, 16000, 15.2, 58.8, 1.42);
			SetMaxShipStats(pchar);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			//UpgradeShipParameter(pchar, "Cannons");
			pchar.ship.HP = 732; */
			//UpgradeShipFull(pchar);
			UpgradeShipParameter(pchar, "Capacity");
			RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull  = "q"; // belamour особый скин
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddCharacterGoods(pchar, GOOD_BALLS, 100);
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddCharacterGoods(pchar, GOOD_POWDER, 220);
			pchar.Ship.name = GetShipName("Adeline");
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_6":
			if (sti(Pchar.money) >= 15000)
				{
					dialog.text = "흠... 사실 하나 있긴 한데, 너한테 어울릴지는 모르겠군.";
					link.l1 = "그래, 지금은 가릴 처지가 아니지. 가진 거 다 보여 줘!";
					link.l1.go = "Sharlie_7";
				}
				else
				{
					dialog.text = "이봐, 나리, 먼저 돈부터 쌓아두고 배에 대해 물어보라고. 알겠어? 여기서 공짜로 주는 건 아무것도 없어. 내 말 이해했지?";
					link.l1 = "알겠어, 굳이 그렇게 무례하게 굴 필요는 없었잖아. 좋아, 돈을 마련하면 다시 올게.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Sharlie_shipwait";
				}
		break;
		
		case "Sharlie_7":
			dialog.text = "그럼 잘 보시오. 최근에 슬루프 한 척을 적당한 값에 샀소. 원래는 해적선이었고, 이전 주인들은 이미 수많은 죄로 안전하게 교수형을 당했지. 솔직히 말해, 이 배는 루거만큼 좋지도 않고 손상도 심하지만, 그래도 바다로 나갈 수는 있소.\n지금은 수리할 시간이 없소 - 내 인부들은 모두 주문받은 브리그 건조에 바쁘거든. 그러니 지금 상태 그대로 나에게서 살 수 있소. 이런 점을 감안해서 평소보다 싸게 팔겠고, 화물창에 있는 것들도 같이 주겠소 - 만오천 페소어치 말이오.";
			link.l1 = "좋아. 배가 바다에 나갈 수 있으면 그걸로 충분하지. 과달루프는 코앞이니, 네가 기회가 없다면 거기서 고치면 되겠지.";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			AddMoneyToCharacter(pchar, -15000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "그렇다면 이 성공적인 구매를 축하드리오. 이제 그 배는 당신 것이오. 잘 써먹길 바라오.";
			link.l1 = "고마워!";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "sloop";
			pchar.questTemp.Sharlie = "crew";
			//стартовый шлюп
			pchar.Ship.Type = GenerateShipExt(SHIP_SLOOP, true, pchar);
			SetMaxShipStats(pchar);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew"); */
			UpgradeShipParameter(pchar, "Capacity");
			AddCharacterGoods(pchar, GOOD_BALLS, 51);
			AddCharacterGoods(pchar, GOOD_GRAPES, 39);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 54);
			AddCharacterGoods(pchar, GOOD_BOMBS, 36);
			AddCharacterGoods(pchar, GOOD_POWDER, 231);
			pchar.Ship.name = "Black Hound";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS3;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_shipwait":
			dialog.text = "그래서, 나리, 돈을 가지고 다시 오셨소?";
			if (sti(Pchar.money) >= 15000)
			{
				link.l1 = "그래, 이제는 허름한 배 하나 살 돈은 모인 것 같아.";
				link.l1.go = "Sharlie_7";
			}
			else
			{
				link.l1 = "아직 충분하지 않아. 그냥 둘러보러 들렀을 뿐이야...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_shipwait";
			}
		break;
//<-- -----------------------------------------Бремя гасконца-----------------------------------------------------
		// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
		case "FMQM_oil_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto5", "FMQM_Looking", -1);
			pchar.questTemp.FMQM = "remove_oil1";
		break;
		
		case "FMQM_oil_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil2";
		break;
		
		case "FMQM_oil_3":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil3";
		break;
		
		case "FMQM_oil_4":
			dialog.text = "이런, 친구야, 우리 둘 다 여기서 고생했구나. 놈들이 송진을 압수해 갔고, 나는 보석금으로 엄청난 돈을 날렸어. 도대체 어떻게 우리 작업을 알아냈던 거지? 내 일꾼 중 하나가 분명히 밀고한 거야... 내가 이 일은 처리할 테니—죄인에게 자비를 베푸소서!";
			link.l1 = "내 모든 노력이 헛수고였다는 말이군...";
			link.l1.go = "FMQM_oil_5";
		break;
		
		case "FMQM_oil_5":
			dialog.text = "정말 유감이오, 선장님. 여기서는 우리가 할 수 있는 게 없소, 운명이란 놈이 가끔은 참 못됐지.";
			link.l1 = "알겠소. 그럼 이만 물러가겠소. 안녕히 계시오!";
			link.l1.go = "FMQM_oil_6";
		break;
		
		case "FMQM_oil_6":
			DialogExit();
			AddQuestRecord("FMQ_Martinique", "12");
			pchar.questTemp.FMQM = "officer";
			pchar.quest.FMQM_advice.win_condition.l1 = "location";
			pchar.quest.FMQM_advice.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FMQM_advice.function = "FMQM_GuideAdvice";
			DeleteAttribute(pchar, "questTemp.FMQM.Oil");
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_x":
            dialog.text = "그 대화로 다시 돌아가고 싶군. 네 배에 어떤 작업이든 해줄 때, 네가 비단을 좀 더 가져다주면... 꽤 큰 할인을 해주지... 아주 큰 할인 말이야...";
			link.l1 = "주인장, 바로 본론으로 들어갑시다. 나는 첩자도 아니고, 도일리 대령의 부하도 아닙니다. 게다가 나는 마커스 타이렉스와 함께 일하고 있소. 그 이름은 익숙할 거라 생각합니다. 그러니 서로 속이지 말고 솔직하게 갑시다. 나는 당신이 비단 돛천을 꾸준히 공급받아야 한다는 걸 알고 있고, 마커스 타이렉스가 그것을 정기적으로 가져다줄 의향이 있습니다. 물론, 가격만 합의된다면 말이죠. 그럼 바로 그 얘기부터 합시다, 주인장?";
			link.l1.go = "mtraxx_x_1";
		break;
		
		case "mtraxx_x_1":
            dialog.text = "좋아. 선택의 여지가 없는 것 같군 – 네가 도일리 놈 밑에서 일해서 날 감옥에 보내든, 아니면 내가 급히 대량의 비단을 구하지 못하면 파산하게 되든 말이야. 한 필당 25두블룬을 지불할 용의가 있지만, 대량 거래만 받아. 최소 100필 이상이어야 해.";
			link.l1 = "그럼 거래가 성사된 거군. 타이렉스가 매달 100두름씩 공급할 수 있을 거라 확신하오.";
			link.l1.go = "mtraxx_x_2";
		break;
		
		case "mtraxx_x_2":
            dialog.text = "그거 정말 훌륭하군! 첫 번째 물량을 바로 살 수 있겠어.";
			link.l1 = "지금 당장은 못 하지만 오래 걸리진 않을 거요. 당신이 필요한 화물을 실은 배가 지금은 캡스터빌에 있소, 내가 곧장 그리로 가서 그 배를 당신에게 보내겠소. 하역은 어디서 하면 되겠소?";
			link.l1.go = "mtraxx_x_3";
		break;
		
		case "mtraxx_x_3":
            dialog.text = "이렇게 하자. 매달 10일부터 15일까지 밤마다 내 사람들이 만에서... 아니, 잠깐, 케이프 네그릴에서 네 손님들을 기다릴 거야. 거리가 꽤 멀긴 하지만, 순찰이 훨씬 적거든... 암호는 '리옹의 상인'이야.";
			link.l1 = "좋소, 장인. 나는 곧바로 캡스터빌로 향하겠소.";
			link.l1.go = "mtraxx_x_4";
		break;
		
		case "mtraxx_x_4":
            dialog.text = "당신 배가 빨리 도착하길 바라오, 나는 새 비단이 몹시 필요하오.";
			link.l1 = "걱정하지 마시오, 모든 게 잘 될 것이오. 행운을 빌겠소!";
			link.l1.go = "mtraxx_x_5";
		break;
		
		case "mtraxx_x_5":
			DialogExit();
            AddQuestRecord("Roger_2", "21");
			pchar.questTemp.Mtraxx = "silk_10"; // покупатель найден
			sld = characterFromId("Jeffry");
			sld.DeckDialogNode = "Jeffry_9";
		break;
		// Jason Исла Мона
		case "IslaMona":
			if (CheckAttribute(pchar, "questTemp.IslaMona.Shipyarder") && pchar.questTemp.IslaMona.Shipyarder == npchar.id)
			{
				if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
				{
					dialog.text = "아니, "+pchar.name+". 나는 자네에게 아무런 감정도 없네만, 먼저 내 나라와의 문제부터 해결하게. 왕실의 적에게 이렇게 귀중한 물건을 파는 건 오해를 살 수 있지.";
					link.l1 = "그래, 그리고 출처가 불분명한 물건을 배에 몰래 실을 땐 아주 친한 친구지? 이 오해 좀 풀고 오라고.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "그렇다고 치자. 왜? 뭘 만들고 있나?";
					link.l1 = "아니, 나는 아주 특별한 임무를 맡았어. 플랜테이션 관리자 일을 위해서지.";
					link.l1.go = "IslaMona_1";
				}
			}
			else
			{
				npchar.quest.IslaMonaTools = "true";
				dialog.text = "도와줄 수 없어.";
				link.l1 = "정말 안타깝군!";
				link.l1.go = "exit";
			}
		break;
		
		case "IslaMona_1":
            dialog.text = "알겠소. 이 관리자 녀석이 자네에게 충분히 챙겨줬기를 바라지. 이런 세트라면 나 같으면 값을 꽤나 불렀을 테니까. 대도시에서 최근에 물건이 들어온 덕에 자네는 운이 좋은 거요.";
			link.l1 = "얼마야?";
			link.l1.go = "IslaMona_2";
		break;
		
		case "IslaMona_2":
			pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
            dialog.text = "천 개의 금화 두블룬.";
			link.l1 = "덥다고? 나는 괜찮아. 내가 가져갈게.";
			link.l1.go = "IslaMona_7";
			link.l2 = "너무 비싸군. 나처럼 전체 세트를 살 사람은 또 없을 거라 의심스럽네. 일부는 팔리겠지만, 일부는 이 동네 부랑자들이 훔쳐가겠지. 할인해 주는 게 어떻겠나?";
			link.l2.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				Notification_Skill(false, 60, SKILL_COMMERCE);
				dialog.text = "반드시 찾아낼 거야. 가격은 변동 없어. 어때? 오래 기다리지 않을 거다.";
				link.l1 = "좋아, 알겠어, 알겠다고. 내가 살게.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 900;
				dialog.text = "좋아, 백 개로 하자. 구백. 그 이하로는 안 돼. 더는 깎아 달라고 하지 마.";
				link.l1 = "나도 안 할 거야. 동의해.";
				link.l1.go = "IslaMona_7";
				link.l2 = "좀 더 주지 그러냐? 내가 도매상으로 사갈게. 그러면 수리랑 도색도 너한테 맡기고, 제일 멋진 선수상도 주문하지.";
				link.l2.go = "IslaMona_4";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
		break;
		
		case "IslaMona_4":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 85)
			{
				Notification_Skill(false, 85, SKILL_COMMERCE);
				dialog.text = "살아 있는 계집을 주문하든 말든 상관없어. 구백이야.";
				link.l1 = "좋아, 알겠어, 알겠다고. 내가 살게.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 800;
				dialog.text = "확실하지? 잊지 않을 거지? 좋아, 백 개 더 자르자. 하지만 이번이 마지막이야!";
				link.l1 = "잊지 않을게. 약속이야!";
				link.l1.go = "IslaMona_7";
				link.l2 = "음, 뭐라고 해야 할까...";
				link.l2.go = "IslaMona_5";
				AddCharacterExpToSkill(pchar, "Fortune", 200);
			}
		break;
		
		case "IslaMona_5":
            dialog.text = "말도 안 돼! "+pchar.name+", 네놈 머리에서 산탄 한 조각 빼는 것도 깜빡했나? 전갈처럼 욕심 많군! 네놈이 최근에 벌인 짓거리들 우리 다 들었어! 이미 금덩이 한 보따리는 챙겼으니, 남들 돈 버는 데 방해하지 마라. 말 한 마디만 더 하면 천 이상 아니면 안 팔 거다.";
			link.l1 = "알겠어, 알겠어! 진정해. 나도 동의해.";
			link.l1.go = "IslaMona_7";
			link.l2 = "하지만, "+npchar.name+", 나한텐 어린 자식들이 있어! 나도 그 애들 생각해야 한다고! 정직하게 화물 운송해서는 돈이 턱없이 부족하단 거, 알잖아!";
			link.l2.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 100)
			{
				Notification_Skill(false, 100, SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
				dialog.text = "사창가 여자들 자식은 사람 취급도 안 해, "+pchar.name+". 너 정말 지긋지긋하다. 통 위에 두블룬 천 개 올려놔, 아니면 이제 끝이다.";
				link.l1 = "무슨 소리야, 아니라니? \n그래. 동의해, 너 사기꾼이잖아.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 800);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 700;
				dialog.text = "자식이 있는 줄은 몰랐어. 그렇게 사정이 안 좋은 줄도 몰랐고. 좋아, 불평하지 마. 칠백이야. 거의 손해 보는 셈이지.";
				link.l1 = "잊지 않을게. 약속이야!";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Fortune", 400);
				Achievment_SetStat(106, 1);
			}
		break;
		
		case "IslaMona_7":
            dialog.text = "그러니까, 너 나한테 빚진 거야 "+sti(pchar.questTemp.IslaMona.Shipyarder.Money)+" 두블룬.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Shipyarder.Money))
			{
				link.l1 = "여기, 마지막 남은 걸 주는 거야, 이제 나한텐 아무것도 없어.";
				link.l1.go = "IslaMona_8";
			}
			else
			{
				if (PCharDublonsTotal() < 1)
				{
					link.l1 = "기다려, 나 사채업자한테 빚지러 간다.";
					link.l1.go = "IslaMona_money_exit";
				}
				else
				{
					link.l1 = "내가 가진 전부야 "+FindRussianDublonString(GetCharacterItem(pchar,"gold_dublon"))+". 이걸 받아, 그리고 나는 고리대금업자들에게 갈게.";
					link.l1.go = "IslaMona_money";
				}
			}
		break;
		
		case "IslaMona_money":
			pchar.questTemp.IslaMona.Shipyarder.Money = sti(pchar.questTemp.IslaMona.Shipyarder.Money)-PCharDublonsTotal();
			Log_Info("You gave "+FindRussianDublonString(PCharDublonsTotal())+"");
			RemoveDublonsFromPCharTotal(PCharDublonsTotal());
			PlaySound("interface\important_item.wav");
            dialog.text = "나한테 미안해할 필요 없어, 네 선실 사물함엔 금이 가득하잖아. 나한테 빚졌어. "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+".";
			link.l1 = "";
			link.l1.go = "IslaMona_money_exit";
		break;
		
		case "IslaMona_money_exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			npchar.quest.IslaMonaMoney = "true";
			pchar.questTemp.IslaMona = "dublon";
		break;
		
		case "IslaMona_8":
			Log_Info("You gave "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+"");
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.IslaMona.Shipyarder.Money));
			PlaySound("interface\important_item.wav");
            dialog.text = "좋습니다. 전액이 준비되어 있군요. 도구들은 당신 배로 전달될 겁니다. 꽤 무거운 상자들이오.";
			link.l1 = "감사합니다, "+npchar.name+"!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			GiveItem2Character(pchar, "islamona_toolbox");
			DeleteAttribute(pchar, "questTemp.IslaMona.Shipyarder");
			DeleteAttribute(npchar, "quest.IslaMonaMoney");
			AddQuestRecord("IslaMona", "2");
			pchar.questTemp.IslaMona = "get_tools";
		break;
	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}

// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	string sSail;
	
	switch (_type)
	{
	    case 1 : sSail = ""+XI_ConvertString("sails_1")+""; break;
	    case 2 : sSail = ""+XI_ConvertString("sails_2")+""; break;
	    case 3 : sSail = ""+XI_ConvertString("sails_3")+""; break;
		case 4 : sSail = ""+XI_ConvertString("sails_4")+""; break;
		case 5 : sSail = ""+XI_ConvertString("sails_5")+""; break;
		case 6 : sSail = ""+XI_ConvertString("sails_6")+""; break;
		case 7 : sSail = ""+XI_ConvertString("sails_7")+""; break;
		case 8 : sSail = ""+XI_ConvertString("sails_8")+""; break;
		case 9 : sSail = ""+XI_ConvertString("sails_9")+""; break;
		case 10 : sSail = ""+XI_ConvertString("sails_10")+""; break;
		case 11 : sSail = ""+XI_ConvertString("sails_11")+""; break;
	}
	return sSail;
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

void SelectFindship_ShipType()
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) <= 27) iRank = 3;
	
	int iShip = SHIP_WAR_TARTANE;
	switch (iRank)
	{
		case 0:
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 1:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break; 
		case 2:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 3:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	pchar.GenQuest.Findship.Shipyarder.ShipType = iShip;
}

// проверка количества материалов для корабельного тюнинга
void checkMatherial(ref Pchar, ref NPChar, int good)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Tuning.Matherial);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial);
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Tuning.Matherial = sti(NPChar.Tuning.Matherial) - amount;
}

/*
  _chr 		- ГГ
  NPChar 	- верфист
  MaterialNum -  номер материала для апгрейда 
	 1 - товар	 
	 2 - цена в дублонах(сундуки)
  Функция возвращает кол-во материала необходимого для данного типа апгрейда	  
*/

int GetMaterialQtyUpgrade( ref _chr, ref _nchar, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	float fQuestShip 	= 1.0;
	float LEcoeff       = 1.0; // legendary edition
		
	int   	shipClass     		= sti(RealShips[sti(_chr.Ship.Type)].Class);	
	int   	shipMinCrew   		= sti(RealShips[sti(_chr.Ship.Type)].MinCrew);	
	int 	shipPrice			= sti(RealShips[sti(_chr.Ship.Type)].Price);	
		
    if(shipClass == 4) LEcoeff = 0.38;
    if(shipClass > 4) LEcoeff = 0.25;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 	fQuestShip = 1.3;	

	if(MaterialNum == 1) 
	{
	int Material 	= makeint((40 * (8 - shipClass) + 25 * MOD_SKILL_ENEMY_RATE + hrand(shipMinCrew)) * fQuestShip * LEcoeff);
	if(Material < 1) 		Material 	= 1;
		return Material;
	}
	if(MaterialNum == 2)
	{
		int WorkPrice 	= 1;
		switch (shipClass)
		{
			case 1: 
				WorkPrice = 10;
			break;
			case 2: 
				WorkPrice = 7;
			break;
			case 3: 
				WorkPrice = 5;
			break;
			case 4: 
				WorkPrice = 3;
			break;
			case 5: 
				WorkPrice = 2;
			break;
			case 6: 
				WorkPrice = 1;
			break;
		}
		return WorkPrice;
	}
	
	return 0;
}
// belamour legendary edition тюнинг - проверка на сделанное
bool TuningAvailable()
{
	int num = 0;
    ref shTo = &RealShips[sti(Pchar.Ship.Type)];

	if(CheckAttribute(shTo, "Tuning.SpeedRate"))    num++;
	if(CheckAttribute(shTo, "Tuning.WindAgainst"))  num++;
	if(CheckAttribute(shTo, "Tuning.Cannon"))       num++;
	if(CheckAttribute(shTo, "Tuning.Capacity"))     num++;
	if(CheckAttribute(shTo, "Tuning.HP"))           num++;
	if(CheckAttribute(shTo, "Tuning.MaxCrew"))      num++;
	if(CheckAttribute(shTo, "Tuning.TurnRate"))     num++;
	if(CheckAttribute(shTo, "Tuning.MinCrew"))      num++;
	
	if(sti(shTo.Class) > 4 && num == 7 && !CheckAttribute(shTo, "Tuning.MinCrew"))
	{
		if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
	}
	
	if(num < 8) return true;
	else
    {
        if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("Ship " + pchar.ship.name + "  gains 5% speed increase on the Global Map!");
        }
        return false;
    }
}
