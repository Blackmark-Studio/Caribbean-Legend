#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	bool bLock = (CheckAttribute(pchar, "GenQuest.BrothelLock")) && (GetCharacterIndex("Mary") != -1);
	bool bLock1 = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) && (IsOfficer(characterFromId("Helena")));

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("마을에 경보가 울렸어. 모두가 너를 찾고 있어! 내가 너라면 여기 오래 머무르지 않겠어.","경비대 전원이 너를 찾으려고 마을을 샅샅이 뒤지고 있어. 나도 바보는 아니니까, 너랑 말 섞을 생각 없어!","도망쳐, 이봐, 군인들이 널 갈기갈기 찢기 전에..."),LinkRandPhrase("뭘 원하지, 이 악당아?! 도시 경비대가 이미 네 뒤를 쫓고 있어. 멀리 못 갈 거다, 해적놈!","더러운 살인자, 내 집에서 나가! 경비병들!!","난 네가 무섭지 않아, 이 개새끼야! 교수대가 널 부르고 있어, 멀리 못 갈 거다..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("헤, 난 경보 따위 신경 안 써...","걔네들은 나를 절대 못 잡아."),RandPhraseSimple("입 닥쳐, "+GetWorkTypeOfMan(npchar,"")+", 아니면 네 썩은 혀를 뽑아버릴 거다.","헤헤, "+GetWorkTypeOfMan(npchar,"")+", 너도 해적 사냥하러 왔어? 이봐, 진정해. 그러면 목숨은 건질지도 모르니까..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"! 어서 오시오, "+GetAddress_Form(NPChar)+" 로스-테케스 광산 선술집에 오시오. 음식, 술, 여자들까지, 모두 저렴한 가격에! 내 이름은 "+GetFullName(npchar)+" 그리고 나는 언제나 당신을 위해 준비되어 있소.";
				Link.l1 = "어디 보자... 나는 "+GetFullName(pchar)+". 만나서 반갑소, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아하, 내 오랜 지인인 선장이군 "+GetFullName(pchar)+"! 반갑다, 영감! 럼주, 여자?";
				if (makeint(pchar.money) >= 5)
				{
					link.l1 = "럼 한 잔 따라줘. "+npchar.name+".";
					link.l1.go = "drink";
				}
				link.l2 = "좀 자고 싶은데. 빈 방 있나?";
				link.l2.go = "room";
				link.l3 = LinkRandPhrase("소식 좀 있나?","여기 근처에 무슨 새 소식 있어?","육지 생활은 어떤가?");
				link.l3.go = "rumours_tavern";
				link.l4 = "아니, 난 아무것도 필요 없어, "+npchar.name+". 그냥 인사나 하려고 들렀어.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "오, 정말 기쁘군! 우리 도시에는 새 얼굴이 드물거든. 럼주 한 잔 따라줄 테니, 우리 얘기 좀 해볼까...";
			link.l1 = "여기 처음 와봤는데, 이 정착지에 대해 좀 더 알고 싶어.";
			link.l1.go = "info";
			if (makeint(pchar.money) >= 5)
			{
				link.l2 = "럼 좀 따라줘. "+npchar.name+".";
				link.l2.go = "drink";
			}
			link.l3 = "잠깐 눈 좀 붙이고 싶은데, 빈 방 있어?";
			link.l3.go = "room";
		break;
		
		case "info":
			dialog.text = "별로 흥미로운 이야기는 없어. 매일 똑같은 일이지: 지루함, 태양, 그리고 먼지뿐이야. 여기엔 군인, 흑인, 인디언만 살고 있지. 금에 굶주린 모험가나 도적들도 가끔 보일 거야\n가끔은 자네 같은 신사, 선장들이 노예를 주괴로 팔거나 귀금속을 사려고 들르기도 해. 우리 상인은 꽤 흥미로운 사람이야. 금과 은 덩이뿐만 아니라 준보석도 팔지\n그 양반 말로는 특별한 지식을 가진 사람이라면 이런 조약돌이 아주 쓸모 있을 거라더군. 그러니 우리 상점 한번 들러봐. 광산 자체는 산 아래 더 깊은 곳에 있어. 원한다면 가볼 수도 있지만, 경비병을 화나게 하진 않는 게 좋을 거야\n죄수들과 말 섞지 말고, 도둑질은 절대 하지 마. 신께서 자네를 지켜주시길. 어쨌든 이 마을에서 제일 좋은 곳은 내 선술집이야. 이 불지옥에서 쉴 수 있는 최고의 곳이지!";
			link.l1 = "정보 고마워!";			
			link.l1.go = "exit";
		break;
		
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 3)
			{
				dialog.text = "선장님, 이제 그만 마시는 게 좋을 것 같소. 술에 취해 소란이라도 피우면 큰일 납니다. 우리 여기선 그런 일에 아주 엄격하오. 선장님의 권위도 소용없을 것이오.";
				link.l1 = "흠... 네 말이 맞아 - 이미 충분히 마셨지. 걱정해줘서 고마워!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -5);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "천만에요, 선장님. 내 최고급 자메이카 흑럼 한 파인트에 은화 다섯 닢만 받지!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("좋아, 자네의 건강과 이 집의 번영을 위하여!","좋아, 바다에 있는 자들을 위하여!","좋아, 네 마을의 번영을 위하여!"),LinkRandPhrase("좋아, 행운의 바람에, 운명의 돌풍에, 우리 모두 더 가볍고 부유하게 살기를!","좋아, 모든 일에 항상 우리 등 뒤에서 불어오는 바람을 위하여!","좋아, 행복과 행운, 기쁨, 그리고 여자들에게!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
		break;
		
		case "room":
			if (CheckAttribute(pchar, "GenQuest.LosTequesSex"))
			{
				dialog.text = "나리, 방이랑 아가씨 값은 이미 치르셨소. 어서 위층으로 올라가시오, 그 아가씨가 한참 기다리고 있었소.";
				link.l1 = "좋아.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "그렇소. 얼마나 머무를 생각이오?";
			if(!isDay())
			{
				link.l1 = "아침까지.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "해질 때까지.";
				link.l1.go = "room_night";
				link.l2 = "다음 아침까지.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "그건 8리알 10개야. 방에 여자도 들일래? 계집애는 천 페소면 돼.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "아니, 여자 필요 없어. 자, 방값으로 이거 받아.";
				link.l1.go = "room_day_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "그래, 방이랑 그 여자 데리고 갈게. 돈 여기 있다.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "아쉽지만, 방값을 감당할 수 없소.";
			link.l3.go = "exit";
		break;

		case "room_day_next":
			dialog.text = "그건 8리알 10개야. 방에 여자도 부를래? 계집애는 천 페소면 돼.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "아니, 여자 필요 없어. 자, 방값으로 이거 받아.";
				link.l1.go = "room_day_wait_next";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "좋아. 방이랑 여자까지 받자. 돈은 여기 있다.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_day";
				}
			}
			link.l3 = "아, 안타깝게도 방값을 감당할 수 없네.";
			link.l3.go = "exit";
		break;

		case "room_night":
			dialog.text = "그건 8리알 10개야. 방에 계집애도 부를까? 계집애 값은 천 페소밖에 안 해.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "아니, 여자 필요 없어. 자, 이걸로 방값 치르지.";
				link.l1.go = "room_night_wait";
			}
			if (makeint(pchar.money) >= 1010)
			{
				if (IsOfficer(characterFromId("Mary")) || !bLock || !bLock1)
				{
					link.l2 = "좋아. 방이랑 여자 데리고 가자. 여기 돈이다.";
					link.l2.go = "room_girl";
					sTotalTemp = "wait_night";
				}
			}
			link.l3 = "아쉽지만, 방값을 감당할 수 없네.";
			link.l3.go = "exit";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -20);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "room_girl":
			AddMoneyToCharacter(pchar, -1010);
			dialog.text = "위층으로 올라가시오, 나리. 그 아가씨가 기다리고 있을 거요. 즐거운 시간 보내시오!";
			link.l1 = "고마워, 친구...";
			link.l1.go = "room_girl_1";
		break;
		
		case "room_girl_1":
			DialogExit();
			pchar.GenQuest.CannotWait = true;
			pchar.GenQuest.LosTequesSex = "true";
			LocatorReloadEnterDisable("LosTeques_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("LosTeques_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			sld = GetCharacter(NPC_GenerateCharacter("MineFuckGirl" , "squaw_"+(rand(2)+1), "woman", "woman_B", 1, SPAIN, 1, true, "quest"));
			sld.dialog.FileName = "Tavern\LosTeques_Tavern.c";
			sld.dialog.currentnode = "MineFuckGirl";
			//sld.greeting = "";
			sld.name = GetIndianName(WOMAN);
			sld.lastname = "";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "LosTeques_tavern_upstairs", "goto", "goto1");
		break;
		
		case "MineFuckGirl":
			dialog.text = "어이, 백인 주인. 쳐다보지 마라 "+npchar.name+" 그렇게, "+npchar.name+" 뭐든지 창녀촌의 백인 계집보다 더 잘할 줄 안다네. 아, 나리, 정말 잘생기셨군요... 약속해요, 이 계집이 오래도록 당신을 사랑할 거예요.";
			link.l1 = "좋아, 네가 가진 최고의 인디언 부적을 보여줘. 비의 춤 같은 건 필요 없겠군, 널 흠뻑 적시려면...";
			link.l1.go = "MineFuckGirl_sex";
		break;
		
		case "MineFuckGirl_sex":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("대낮에 강도질이라니!!! 여기서 무슨 일이야?! 잠깐, 기다려 봐, 이 친구...","이봐, 거기서 뭐 하는 거야?! 나 털려고 하는 거냐? 이제 큰일 났다...","잠깐, 지금 뭐 하는 거야? 결국 도둑이었군! 여기서 끝이다, 이 자식아...");
			link.l1 = LinkRandPhrase("악마다!","젠장!","아, 젠장");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
