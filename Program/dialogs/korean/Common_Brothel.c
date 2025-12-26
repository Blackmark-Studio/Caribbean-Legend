void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1, iColony, crewWhoreCost, charWhoreCost = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
		
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	crewWhoreCost = 50 + 7 * MOD_SKILL_ENEMY_RATE - hrand(40);
	charWhoreCost = 2460 + sti(pchar.rank) * 40;
	
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("무슨 여자들이야, 이 사람아?! 주둔군 절반이 너 뒤쫓고 있는데, 넌 곧장 사창가로 오다니!","꺼져, 알겠어? 주둔군 절반이 너 뒤쫓고 있어!")+"","모든 도시 경비병들이 너를 찾고 있어. 지금 이 순간 너한테 서비스를 제공할 만큼 내가 바보는 아니지 ...","여기서 할 일 없어!"),LinkRandPhrase(""+GetSexPhrase("내 여자들한테 손대기만 해 봐라, 산 채로 가죽을 벗겨줄 테니까!","꺼져, 이놈아!")+"","Dirty"+GetSexPhrase("","")+" 살인자야, 당장 내 가게에서 나가! 경비병들아!!!","나는 너 따위 안 무서워, "+GetSexPhrase("놈","쥐")+"! 곧 우리 요새에서 교수형을 당하게 될 거다, 멀리 못 갈 거야..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("헤, 경보 따위는 나한텐 아무 문제도 아니지...","걔네들은 절대 나를 못 잡아."),RandPhraseSimple("닥치라고, 이 멍청한 노파야.","말썽나기 싫으면 입 다물어..."));
				link.l1.go = "exit";
				break;
			}
			//--> Мерзкий Божок
			if (CheckAttribute(pchar, "questTemp.ChickenGod.HostessDialog")) {
				dialog.text = "오, 맙소사! 어떻게 여기 들어오신 거죠? 존경하는 선장님, 제발 나가 주십시오 – 부탁드립니다! 저희 업소는 지금 영업하지 않습니다!";
				link.l1 = "반가워요, 그대 "+npchar.name+". 나는 초대 손님 명단에 있었어. 하지만 이런 곳에서는 손님도 돈을 내야 하니까... 너무 곤란하게 하지 말아 줘, 하지만 방값은 내가 내고 싶어.";
				link.l1.go = "chicken_god";
				
				DeleteAttribute(pchar, "questTemp.ChickenGod.HostessDialog");
				break;
			}
			//<-- Мерзкий Божок
			//--> туториал Мартиника
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start" && npchar.location == "FortFrance_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				link.l1 = "듣지, 오로라. 오늘 밤 같이 있을 여자가 필요해. 그리고 집에 데려가고 싶어. 그거 좀 어떻게 해줄 수 있겠어?";
                link.l1.go = "Gigolo";
				break;
			}
			//<-- туториал Мартиника
			//Jason --> Заносчивый аристократ
			if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && !CheckAttribute(pchar, "questTemp.ZA.Block") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
			{
				dialog.text = "당신은 정말 훌륭한 분이시군요. 게다가 우리 아가씨들도 당신을 무척 좋아합니다. 제 업소를 위해 작은 부탁 하나 드리고 싶습니다.";
				link.l5 = "칭찬해 주시니 영광이오. 무슨 일로 내 도움이 필요하시오?";
				link.l5.go = "Badboy";
				link.l8 = "미안하지만, 지금은 바빠.";
				link.l8.go = "exit";
				npchar.quest.Badboy = "true";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
			{
				if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
				{
					dialog.text = "오, 돌아오셨군요! 그 일은 준비하셨습니까 "+pchar.GenQuest.Badboy.Brothel.Name+" 내 여자애들을 내버려 두라고?";
					link.l5 = "그래. 그는 더 이상 여기 나타나지 않을 거야.";
					link.l5.go = "Badboy_complete";
				break;
				}
			}
			// <-- Заносчивый аристократ
			
			//--> Jason Португалец
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (!CheckAttribute(pchar, "questTemp.Portugal") && bOk && !CheckAttribute(npchar, "quest.Portugal") && npchar.location == "Marigo_SecBrRoom" && makeint(environment.time) > 6.0 && makeint(environment.time) < 22.0 && sti(pchar.rank) >= 7)
				{
					DelMapQuestMarkCity("marigo");
					DelLandQuestMark(npchar);
					dialog.text = "선장님, 부탁 하나 드려도 되겠습니까?";
					link.l5 = "마님을 위해서라면 뭐든지 해드리겠습니다! 언제든지 부르십시오!";
					link.l5.go = "Portugal";
					link.l8 = "미안하지만, 지금은 바쁘네.";
					link.l8.go = "exit";
					npchar.quest.Portugal = "true";
					DelLandQuestMark(npchar);
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				dialog.text = "휴고와 이야기해 보셨습니까, 선장 나리?";
				if (sti(pchar.money) >= 10000)
				{
					link.l1 = "게다가, 부인, 여기 돈이 있습니다. 모든 일이 아주 순조롭게 진행됐습니다...";
					link.l1.go = "Portugal_3";
				}
				else
				{
					link.l1 = "네, 당신의 부탁을 그에게 전했습니다.";
					link.l1.go = "Portugal_exit";
				}
				break;
			}
			//<--Португалец
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "이런, 이것 좀 봐! 찰리 프린스, 그 유명한 커세어잖아! 직접 보게 되다니!";
				link.l1 = RandSwear()+"안녕, 자네트. 나는 마커스 타이렉스의 임무로 여기 왔어.";
				link.l1.go = "mtraxx_R";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "잊지 못할 회복 치료를 받을 준비가 되었나, 용감한 코르세어?";
				if (sti(pchar.money) >= 31000)
				{
					link.l1 = "나야! 찰리 프린스는 돈은 펑펑 써도 말은 아끼지, 하하!";
					link.l1.go = "mtraxx_R2";
				}
				else
				{
					link.l1 = "거의 다 됐는데... 네 가게에서 지갑을 잃어버린 것 같아... 돈 가지고 다시 올게!";
					link.l1.go = "exit";
				}
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". 사랑의 집에 온 걸 환영하오. 내 이름은 "+npchar.name+", 그리고 내가 주인이오. "+GetSexPhrase("무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?","솔직히, 여기서 당신을 보게 되어 좀 놀랐소, "+GetAddress_Form(NPChar)+", 하지만 저희는 남성뿐만 아니라 모두에게 서비스를 제공한다는 점을 확실히 말씀드릴 수 있습니다.")+"",TimeGreeting()+". 환영하오, "+GetSexPhrase("이방인","아가씨")+", 제 누추한 가게에 오신 것을 환영합니다. 제 소개를 드리자면, 저는 "+NPChar.Name+" - 여인 손길을 그리워하는 사내들을 위한 이 안식처의 주인이오. "+GetSexPhrase("무엇을 도와드릴까요?","여자들에게도 관심이 좀 있지...")+"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting()+". 무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?",TimeGreeting()+". 무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?");
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))//не идёт квест девочки
			{
				if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// нет запрета от Мэри 280313
				{
					link.l2 = npchar.name+", 네 여자들 중 한 명과 좋은 시간 좀 보내고 싶어.";
					link.l2.go = "Hostess_1";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идёт старт Шарля
			{
				if (sti(pchar.ship.type) != SHIP_NOTUSED && GetCrewQuantity(pchar) > 0) // Rebbebion - а смысл, если нет как корабля, так и команды?
				{
					link.l3 = "내가 마지막으로 내 부하들을 챙긴 지도 꽤 됐군. 우리 선원들을 위해 여자들을 대량으로 주문할 수 있을까?";
					link.l3.go = "ForCrew";
				}
			}
			link.l4 = "질문이 있어.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// генератор  "Найденные документы"
				}
				else
				{
					link.l4.go = "quests";
				}	
			}
			else
			{
				link.l4.go = "quests";//(перессылка в файл города)
			}	
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = "들어봐, "+npchar.name+", 나는 총독의 반지를 찾고 있어. 그가 네 여관에 머물렀고 아마 여기서 잃어버린 것 같아.";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра

			// belamour ночной приключенец -->
			if(CheckAttribute(pchar, "GenQuest.NightAdventureVar") && pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleWhoreMoney")
			{
				link.l8 = "이봐, 네가 가진 최고의 아가씨를 데리고 싶어.";
				link.l8.go = "NA_Girl";
			}
			// <-- приключенец
			link.l9 = "신경 쓰지 마, 난 이미 떠나고 있어.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("무슨 일이야, 잘생긴 녀석?","듣고 있습니다, 선장님.");
				link.l1 = "들어봐, "+npchar.name+", 나는 당신네 기관의 개인 방에서 이 서류들을 발견했소 ...";
				link.l1.go = "ShipLetters_2";				
		break;
		
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "내가 좀 볼까! 흠... 어떤 선장이 서류를 잃어버렸다고? 이 일에 대해서는 항만 관리자에게 물어보는 게 좋겠어.";
				link.l1 = "아마도, 아마도...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "내가 한번 볼게! 오! 이름을 보아하니, 이건 우리 마을의 훌륭한 시민이자 존경받는 고객님의 것이군. 이 서류는 내가 직접 그분께 전달할 수 있어.";
				link.l1 = "아마 아닐 거야...";
				link.l1.go = "exit";
				link.l2 = "훌륭하군! 좋은 사람과 훌륭한 가게라면 언제든 기꺼이 도와주지.";
				link.l2.go = "ShipLetters_3";										
			}	
		break;
		
		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "2");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+GetSexPhrase("손님을 모시는 건 언제나 기쁘죠. 자, 잘생긴 분 – 이미 누군가를 골랐나요, 아니면 별로 상관없으신가요?","글쎄, 내 아가씨들이 분명히... 도와줄 수 있지. 이미 누구 고르셨나, 아니면 별로 상관없으신가?")+"";
					Link.l1 = ""+GetSexPhrase("헤, 난 그냥 창녀 하나만 있으면 돼. 지금 당장 필요하거든. 누가 되든 상관없어, 네 여자들은 다 좋아 보여...","자기 임무만 알면 누구든 괜찮지, 물론...")+"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "그래, 하나 있지, "+GetSexPhrase("내 마음을 사로잡은 사람...","그녀가 가장 착할 텐데...")+"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "오늘은 너한테 줄 수 있는 여자가 없어, 손님이 너무 많거든. 내일 다시 오면 후회하지 않을 거야!";
					Link.l1 = "아쉽군, 이제 막 재미를 붙였는데.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "흠. 이미 그 여자를 위해 돈을 냈잖아. 제발, 나를 방해하지 마.";
				Link.l1 = "알겠어, 간다.";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = "지금은 빈 아가씨가 없어. 며칠 뒤에 다시 와봐.";
				Link.l1 = "좋소, 말씀대로 하겠습니다.";
				Link.l1.go = "exit";	
			}
			else
			{
				// belamour legendary edition Орден Святого Людовика -->
				if(IsEquipTalisman9() && npchar.nation == FRANCE)
				{
					dialog.text = ""+GetSexPhrase("좋아, 이놈아, 그거 참 훌륭하군!","전부 능숙하게 훈련시켰으니, 걱정 말게.")+"내가 소개해줄 수 있는 아름다운 여자가 있는데, 이름은 "+GetFullName(sld)+", 이제 그녀는 자유야.\n오, 거기 그렇게 수줍게 숨기고 있는 건 뭐지?! 저게 프랑스 최고의 훈장 아니야? 저 휘장을 지닌 자들은 전장에서만 전설이 아니라는 소문이 있지... 내 말 무슨 뜻인지 알겠지, 내 해적 친구... 게다가 누구라도 네 '훈장'을 만지는 걸 영광으로 여길 거야, 그러니 오늘 밤은 내 술집에서 공짜로 쉬어. 거절은 안 받아, 잘생긴이.";
					Link.l1 = "물론 동의하지, 무슨 질문이 더 있겠어?!";
					Link.l1.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
					break;
				}
				// <-- legendary edition
				dialog.text = ""+GetSexPhrase("좋아, 훌륭해, 내 용맹한 녀석!","그들은 모두 자기 일에 아주 능숙하니, 의심하지 마시오.")+" 아주 예쁜 아가씨를 소개해 줄 수 있어, 이름은 "+GetFullName(sld)+", 그리고 지금 그녀는 이용할 수 있어. 그 쾌락은 비용이 들지. "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". 동의하나?";
				Link.l1 = "아니. 그런 것 같지 않아. 너무 비싸서...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
				{
					Link.l2 = "물론이지, 내가 어떻게 거절하겠어?!";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "이런 젠장, 나한테 그만한 돈이 없어...";
					Link.l1.go = "exit";
				}
			}
		break;
		
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				dialog.text = "좋아, "+GetSexPhrase("잘생긴","아름다운")+". "+sld.name+" 2층의 개인실에서 당신을 기다릴 것입니다.";
				Link.l1 = ""+GetSexPhrase("좋아, 간다, 그럼","좋아, 간다, 그럼")+"...";
				Link.l1.go = "exit";
				// belamour legendary edition деньги только без ордена или адмиральского мундира
				if(IsEquipTalisman9())
				{
					if(npchar.nation != FRANCE) AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				else
				{
					AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				sld.dialog.currentnode = "Horse_ReadyFack";			
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
				
				// генератор найденных бумаг
				
				// belamour legendary edition не давать квесты губернатору и адмиралу
				bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor");
				bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4;
				
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10 && !MCGovernon && !MCAdmiral ) 
				{					
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;	
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;
										
					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//ложим бумаги в итем								
					sTemp = "_Brothel_room";	
					sTemp1 = "_town";					
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
					Log_QuestInfo("The papers are in location " + sld.startLocation + ", in locator " + sld.startLocator + " p1 : " + p1);
					
					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";
					
					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты 
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");					
				}
				// генератор - "Повод для спешки"
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !MCGovernon && !MCAdmiral) // Addon-2016 Jason
				{
					iColony = FindColony(npchar.city);	
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";					
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");	
					}	
				}				
			}
			else
			{
				dialog.text = "아, 그게 말이오, 문제는 말이지 "+sld.name+" 값싼 여자가 아니야, 그녀의 값은 "+FindRussianMoneyString(sti(sld.quest.price)+charWhoreCost)+". 그리고 지금은 그 배를 살 형편이 안 되는 것 같군. 부자가 되면 다시 오라고\n"+GetSexPhrase(", 그대여","")+"...";
				Link.l1 = "이게 내 팔자지...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "나는 언제나 아가씨들과 손님들이 서로 좋은 감정을 갖게 되면 기쁘지... 그녀의 이름을 말해 보게.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
		
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "흠... 착각하신 것 같군요. 내 업소에는 그런 아가씨가 없어. 혹시 이름을 잘못 들은 거 아닙니까?";
				Link.l1 = "흠... 하지만 방금 전에 그녀와 얘기했는데.";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "아마도. 확실히 하려면 그녀의 이름을 다시 한 번 물어보는 게 좋겠어. 이 일에 대해서는 나중에 다시 얘기하지.";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld)+", 그녀 얘기하는 거야?";
				Link.l1 = "그래, 그녀 말이야.";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "아니, 그녀가 아니야.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		
        case "Hostess_Choice_2":
			dialog.text = "그렇다면 그녀의 이름을 다시 한 번 말해 보시오. 그러면 내가 누구를 말하는지 알게 될지도 모르겠군.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "아마도. 확실히 하려면 그녀의 이름을 다시 한 번 물어보는 게 좋겠어. 이 일에 대해서는 나중에 다시 얘기하지.";
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "흠... 부하들이 '기분 좀 풀게' 해주고 싶으신가요? 이곳은 제 자랑스러운 업소라 최고의 아가씨들이 있답니다. 하지만 항구의 처녀들도 몇 명 알고 있으니, 그들이 선원들 모두를 기쁘게 해줄 거예요. 그건 비용이 좀 들겠네요\n "+FindRussianMoneyString(GetCrewQuantity(pchar)*crewWhoreCost)+".";			
			link.l1 = "좋아, 동의하지.";
			link.l1.go = "ForCrew_1";
			link.l2 = "그거 없이도 알아서 하겠지...";
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*crewWhoreCost && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*crewWhoreCost));
	            AddCrewMorale(Pchar, 10);
				ChangeCharacterComplexReputation(pchar,"authority", 1);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = "내 알 바 아니지만, 먼저 선원 고용할 만큼 돈을 벌고 나서야 그들의 사기를 걱정하는 게 맞다고 생각해.";
			    link.l1 = "아마 네 말이 맞을 거야...";
			    link.l1.go = "exit";
		    }
		break;
		
		case "Woman_FackYou":
			dialog.text = "이런, 도대체 뭐 하는 거야?! 그럴듯한 선장처럼 보였는데... 이번엔 못 도망가, 잘생긴이. 경비병들이 네 날개를 꺾어버릴 거야...";
			link.l1 = "닥쳐, 이 늙은 년아.";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = "나는 반지를 못 찾았어.";
			link.l1 = "그리고 네 여자들은?";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		
		case "TakeMayorsRing_H2":
			dialog.text = "그들도 못 봤어요. 손님이 뭔가를 잊거나 잃어버리면, 내 아가씨들이 나한테 가져다줍니다. 하지만 아무도 총독의 반지는 가져오지 않았어요.";
			link.l1 = "알겠소... 하지만 혹시 그들이 그걸 자기들만 가지려고 한 건 아닐까?";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		
		case "TakeMayorsRing_H3":
			dialog.text = "그럴 리 없지. 아가씨들은 손님들에게 받은 선물만 가질 수 있어, 그게 전부야.";
			link.l1 = "알겠소. 고맙소, "+npchar.name+".";
			link.l1.go = "exit";
		break;
		
		case "Hostess_inSexRoom":
			dialog.text = "아, 거기 있었군...";
			link.l1 = "여기 있습니다, 나리!";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришёл
			NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
			{
				sld = CharacterFromID(pchar.RomNaTroih_Shluha);
				dialog.text = ""+sld.name+"! 내 영웅이여, 아래층에서 시간을 헛되이 보내지 않았군!";
				link.l1 = "이 약함을 용서해 주시겠습니까, 나의 여왕님?";
				link.l1.go = "RomNaTroih_2";
			}
			AddDialogExitQuestFunction("SexWithHostess_fack");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.RomNaTroih");
            if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 10);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 5);
		break;
		
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("여기서 나가는 게 좋을 거야!","마을의 모든 경비병들이 너를 찾고 있어! 어서 떠나는 게 좋겠어...","네가 엉망진창을 만들어 놓고 이제 와서 여기 나타난 거야?! 아니, 이번엔 안 돼..."),LinkRandPhrase("꺼져!","더러운 살인자, 당장 꺼져라! 경비병!","나는 너 따위 안 무서워,"+GetSexPhrase("악당","쥐")+"! 곧 우리 요새에서 교수형을 당할 거다, 멀리 못 도망가..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("헤, 경보 따위는 나한텐 아무 문제도 아니지...","절대 나를 잡지 못할 거야."),RandPhraseSimple("헤, 참 어리석은 계집이구나...","입 다물어, 창녀야, 아니면 내가 다른 걸로 네 입을 막아버릴 테니까..."));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("안녕하세요, "+GetAddress_Form(NPChar)+""+GetSexPhrase("",", 히히...")+". 세뇨라를 만나서 주문서를 작성해야 해.","또 당신이군? 관리인과 이야기해 보시오. 그녀는 사무실에 있어.","봐, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", 다른 일에도 말할 때만큼이나 고집이 세길 바라오... 또 한 번이군","다시 한 번")+" 이곳 주인을 만나 주시기 바랍니다.","오, "+GetAddress_Form(NPChar)+""+GetSexPhrase(", 너 참 고집 세구나!",", 히히... 너 참 고집 세구나?")+" 세뇨라를 만나서 주문서를 작성해야 해.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("좋아, "+GetSexPhrase("아가씨, ","")+"알겠어"+GetSexPhrase("","")+".","그래, 그렇지...",""+GetSexPhrase("의심하지 마, 예쁜이, 나는 황소처럼 고집 세고 힘도 세다!","그래, 그래...")+"",""+GetSexPhrase("이런 젠장, 뭔가 놓친 게 있나 보군... 미안해, 자기야.","좋아, 알겠어.")+"",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "그녀는 어디에 있지?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+GetSexPhrase("오, 아름다운 이여, 그대의 눈동자에 빠져 죽을 수도 있겠군...","아름다워 보여, 자기야!")+"",""+GetSexPhrase("있잖아, 이렇게 아름다운 여자는 처음 봐!","있잖아, 이렇게 사랑스러운 아가씨는 처음 봐!")+"",""+GetSexPhrase("여보, 정말 아름다워 보여요.","젠장, 그 촌놈들한테 정말 질렸었지... 그런데 너는 정말 매력적이야!")+"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase("들어봐, "+GetSexPhrase("아름다움","여보")+", 혹시 여기서 결혼반지를 본 적 있나? 누군가 잃어버린 것 같은데...","여보, 혹시 근처에서 결혼반지나 비슷한 걸 본 적 있어?","들어봐, "+GetSexPhrase("내 고양이","자기야")+", 여기서 결혼 반지 못 봤어?");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_"+reload_location_index+"_2")
			{
				link.l6 = "이봐, 이쁜이. 마커스 타이렉스가 날 보냈어, 이 호박 목걸이 좀 봐봐...";
				link.l6.go = "mtraxx";
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		
        case "Horse_1":
			dialog.text = "그녀는 자기 사무실에 있어. 여기서 길 건너편 문으로 들어가면 되고, 아니면 집 반대편 거리 쪽에서도 들어갈 수 있어. 이름은\n "+characters[GetCharacterIndex(npchar.city+"_Hostess")].name+".";
			Link.l1 = "알겠군. "+GetSexPhrase("여보","여보")+", 감사합니다.";
			Link.l1.go = "exit";			
		break;
		
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("아이고, 그런 말 들으니 정말 기쁘네! 이봐, 지금 한가하니까 나를 고르면 후회하지 않을 거야...","정말 그렇게 생각해? 있잖아, 참 다정하네... 지금 한가하니까, 나를 선택해도 돼."+GetSexPhrase(" 당신에게 사랑의 바다와 애정의 대양을 약속하오...","")+"",""+GetSexPhrase("그렇게 생각하시오? 오, 정말 영광이군. 사실 그런 칭찬은 좀처럼 듣지 못하거든...","아이고, 아가... 너만 알았으면 좋겠구나, 내가 촌놈들한테 얼마나 질렸는지...")+" 이봐, 들어봐. 지금 한가하니까, 나를 골라서 기분 좋게 해줄 수 있어. 실망시키지 않을게, 약속해...");
				if (CheckAttribute(pchar, "questTemp.RomNaTroih") && !CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
				{
					link.l1 = "내 사랑, 바로 그걸 하려던 참이었어! 마침 주인장이 이미 위층에서 나와의 비밀스러운 만남을 준비해 두었지. 같이 갈래?";
					Link.l1.go = "RomNaTroih_1";
					pchar.questTemp.RomNaTroih_Pogovoril = true;
					break;
				}
				link.l1 = "그럼, 너로 정하겠다!";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+GetSexPhrase("아니, 그건 그저 아름다운 숙녀에게 한 칭찬이었어","그건 그냥 칭찬이었어")+".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+GetSexPhrase("내 말 알아듣겠어, 자기야? 이런 싼티 나는 말장난 필요 없어. 거래를 하든가 아니면 꺼져!","그거면 충분해! 여자들한테 칭찬받는 거 말이야!")+"",""+GetSexPhrase("여자들이 귀로 사랑한다고 생각하는 부류인가? 글쎄, 자기야, 그건 사실이 아니야. 나를 원한다면 마담에게 돈을 내고 쓸데없는 말은 삼가줘.","아가씨, 쓸데없는 말로 시간 낭비하지 마. 진짜로 할 생각이면, 돈부터 내...")+"",""+GetSexPhrase("오, 또 한 명의 쾌락을 즐기는 사람이군... 돈만 내면 난 네 거야. 이렇게 간단한 거지, 괜한 감상 따윈 필요 없어!","무슨 일이야, 자기야? 쾌락을 즐기고 싶으면 돈이나 내고 헛소리 그만해!")+"");
				link.l1 = "오, 이 힘 좀 봐!";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
		
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city+"_Hostess")].name+" 그녀의 사무실에서 모든 절차를 마친다. 가서 그녀를 만나봐라"+GetSexPhrase(", 나의 영웅,","")+" 그리고 내 이름을 말해 - "+npchar.name+"... 기다리고 있겠어...";
			Link.l1 = "알겠어, 자기야, 금방 돌아올게...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat("이미 지불하셨습니다.","위층으로 올라가라고 했잖아.","위층이야, 젊은이.","어떤 사람들은 참 느리게 생각하는군...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("그래, 알아.","기억나.","아, 그만 좀 반복해. 기억하고 있어.","흠, 무슨 뜻이야?",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("나는 너를 잘 이해하지 못하겠어."+GetSexPhrase(" 처음엔 칭찬을 하더니, 약속을 어기네. 참 이상한 사람이군...","")+"","또 칭찬이야?","관리인은 자기 사무실에 있어. 알겠어?","우리는 손님을 모욕하면 안 되지만, 너 정말 한마디 듣고 싶게 만드네"+GetSexPhrase("","")+"...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("그냥 그렇게 된 거야...","알겠어, 그렇게 할게.","그래, 알았어.","실례했어, 내 사랑.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "칭찬 고마워. 나를 데려가고 싶으면 그냥 마담한테 가 봐. 평소처럼 하는 거지.";
				Link.l1 = "알겠네.";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("여보, 우리 이미 다 이야기했잖아. ","")+"너무 오래 기다리게 하지 마라...",""+GetSexPhrase("흠... 들어봐, 자기야, 나","I")+" 네 말이 듣기 좋긴 한데, 본론으로 들어가 주겠나...","이 문제를 마담과 상의해 보시겠습니까, 그렇지 않습니까?","흠... 뭐라고 해야 할지 모르겠네...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("나는 절대 그렇게 안 해, 기다려!","물론이지!","물론이오, 말씀대로 하겠소!","나는 이미 당신네 마님을 뵈러 달려가고 있소...",npchar,Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "나는 너를 기다리고 있었는데, 넌 나를 데리러 오지 않았어... 그게 마음에 들었다고는 할 수 없지...";
					Link.l1 = "있잖아, 그냥 그렇게 된 거야...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "오, 또 당신이군, 내 "+GetSexPhrase("영광스러운 해적","예쁜 아가씨")+"! 또 날 원하면 마님을 찾아와. 절대 실망하지 않을 거야..."+GetSexPhrase(" 그런데 말이야, 자기야, 나는 너를 알아봤지만 우리한테는 모든 손님을 똑같이 대하라고 들었거든. 특별 대우는 없어, 미안해...","")+"";
				Link.l1 = "걱정하지 마, 자기야. 조금만 더 기다려 줘, "+GetSexPhrase("귀요미","귀요미")+", 그리고 곧 다시 사적으로 만날 수 있을 거야.";
				Link.l1.go = "exit";
				Link.l2 = "나를 기억해줘서 정말 고맙지만, 오늘 밤은 함께할 수 없어, 미안해.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("그래,"+GetSexPhrase(" 친애하는 친구여,","")+" 일이나 하는 게 좋을 거야. 아무것도 안 하는 것보단 낫지.",""+GetSexPhrase("흠, 왜 너는 ","왜 그러는 거야")+" 똑같은 말을 계속 반복하는 거야?","이봐, 그만하면 됐잖아?!","흠, 놀랍군, 별다른 소식도 없네"+GetSexPhrase(", 또다시 그 어설픈 매력 발산이냐! 나랑 자고 싶으면 마담한테나 가, 이 멍청아!","...")+"","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("그래, 들었어"+GetSexPhrase("","")+" 너...","흠, 그렇게 되는군...","흠, 이쯤이면 충분할지도 모르겠고, 아닐지도 모르겠네...","말 조심해"+GetSexPhrase(", 염소야","")+"...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "오, 또 너냐! "+GetSexPhrase("그리고 또다시, 저 멍청한 칭찬들뿐이군. 이 세상은 정말 변하지 않아... 만약\n ","그냥 상기시켜 주겠네: 만약 ")+"하고 싶어"+GetSexPhrase("즐거운 시간 보내시오","즐거운 시간 보내시오")+" 나랑 있든 말든, 주인에게 돈이나 내. 네 말 따위엔 전혀 관심 없어.";
				Link.l1 = "그건 그다지 놀랄 일도 아니지...";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1_Add":
			dialog.text = "기쁘다고는 할 수 없군... 아쉽네.";
			Link.l1 = "미안하오...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		
		//===>> секс
        case "Horse_ReadyFack":
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
			{
				dialog.text = "아, 드디어 도착했군! 훌륭해! 이제는 자유롭게 말할 수 있어, 아무도 듣고 있지 않으니까...";
				Link.l1 = "그래서, 파란 호박을 준 사람이 그 스페인 놈이었나?";
				Link.l1.go = "mtraxx_2";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SantoDomingo");
				break;
			}
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("당신을 만나서 정말 기쁩니다. "+GetSexPhrase("그럼, 이제 뭘 할 거야?","우리 한번 즐겨볼까?")+"","부끄러워하지 마라"+GetSexPhrase(", 적어도 두 시간은 편히 쉬고 계십시오.",". 널 충분히 즐겁게 해줄 수 있으니, 걱정 마.")+"");
					Link.l1 = RandPhraseSimple("지루하지는 않을 것 같은데...",""+GetSexPhrase("즐겁게 놀자, 자기야!","시간 낭비하지 말자!")+"");
				break;
				case "1":
					dialog.text = "오, 또 당신이군, 내 "+GetSexPhrase("영광스러운 코르세어! 내가 약속한 것이 있으니 이제 그 약속을 지킬 준비가 되었소","예쁜 아가씨! 앞으로 두 시간은 절대 잊지 못할 거야")+"...";
					Link.l1 = "이거 꽤 솔깃한데...";	
				break;
				case "2":
					dialog.text = "오, 드디어 왔군. 시간 낭비하지 말자!";
					Link.l1 = ""+GetSexPhrase("하지 말자, 겁쟁이야...","이제 네가 뭘 할 수 있는지 보여줘...")+"";
				break;
			}
			if (pchar.sex == "woman")
			{
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex";
				AddDialogExitQuest("PlaySex_1");
				// кач от борделя
				if (CheckNPCQuestDate(pchar, "BrothelSex"))
				{
					if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
					else 												AddCharacterHealth(pchar, 5);
					SetNPCQuestDate(pchar, "BrothelSex");
				}
				// изменение статусов
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "FencingS", -15);
				AddCharacterExpToSkill(pchar, "Pistol", -15);
			}
			else
			{
				pchar.horsekiss = npchar.id;
				Link.l1.go = "Horse_Kiss";
			}
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
		break;
		
		case "Horse_Kiss":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("Horse_Kiss", "");
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = "선장님, 왜 그렇게 말이 없으십니까?";
				link.l1 = LinkRandPhrase("그래, 그게 나야.","다음에 이야기하자.",RandPhraseSimple("말하라고 돈 주는 거 아니야.","하지만 너, "+GetSexPhrase("아름다움","여보")+", 그동안 그렇게 조용하지는 않았지."));
				link.l1.go = "exit";
				link.l2 = ""+GetSexPhrase("정말 대단했어, 정신을 잃을 뻔했지! 이렇게 아름답고 매혹적인 여자를 만나는 건 정말 드문 일이야","오, 정말 여자를 기쁘게 하는 법을 아는구나... 너무 설레는걸.")+".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("마음에 들었어?","그래서, 어떻게 생각해? 다 괜찮았어?","그래,"+GetSexPhrase(" 코르세어, 모든 게, 다"," 모든 것")+" 좋아?");
						Link.l1 = RandPhraseSimple(""+GetSexPhrase("물론이지, 다 괜찮아","자네는 분명히 자기 임무를 잘 알고 있군")+".",""+GetSexPhrase("다 괜찮아, 자기야","있잖아, 난 꽤 만족했어")+".");
						Link.l1.go = "exit";
					break;
					case "1":
						dialog.text = LinkRandPhrase("그래, 내가 약속을 지켰나?","그래,"+GetSexPhrase(" 나를 마음에 들어했어?",", 마음에 들었어?")+"?","바라네, "+GetSexPhrase("네가 기뻤다니 다행이야, 나는 정~말 기쁘거든","내가 최선을 다했으니 당신이 기뻐했지")+"...");
						Link.l1 = RandPhraseSimple("그래, 나 진짜 마음에 들었어.",""+GetSexPhrase("정말 즐거운 시간이었어, 너 정말 눈부시게 아름다웠어!","모든 게 정말 끝내줬어!")+"");	
						Link.l1.go = "exit";
					break;
					
					case "2":
						dialog.text = RandPhraseSimple("자, 이제 끝났으니 가야 해.","네 시대는 끝났다,"+GetSexPhrase(" 선장님,","")+".");
						Link.l1 = RandPhraseSimple("그래, 또 보자...","안녕히 가십시오, 그리고 감사합니다...");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "그래서, 여기 어땠어?";
				link.l1 = "이봐, 미녀야, 근처에서 여행 가방 못 봤어?";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("언제 한 번 또 들르시오...","안녕히 가십시오. 언제든 기다리고 있겠습니다...","다시 여기 오시면 반가울 거예요...");
				Link.l1 = "좋아...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = "손잡이가 달린 그 갈색 상자였나?";
			link.l1 = "그래, 뭐 그런 거지...";
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = "그 상자의 주인이 나타나지 않아서, 부인께서 그것을 자신의 부두아르로 가져가셨소.";
			link.l1 = "고마워, 자기야. 잘 가.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		// --> генератор - "A reason to hurry"
		case "Horse_ReasonToFast_1":
			dialog.text = "언제든 들르시오, 항상 반가울 테니. 당신은 참\n "+GetSexPhrase("온화해, 다른 놈들과는 달라","점잖지, 저런 거친 놈들과는 달라")+" 인사도 없고, 작별도 없으며, 종종 해치려고까지 하지...";
			link.l1 = "그게 무슨 뜻이야?";
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "방금 전까지 상사 한 명이 있었어. 평소엔 우리한테 잘 안 오는데, 이번엔 무슨 악마가 그놈을 여기로 끌고 온 거지. 게다가 나를 골랐어... 몇 분 동안 내 위에서 투덜거리더니, 내가 실력이 부족하다고 하더군. 그러고는 어느 만으로 급히 달려갔어. 너무 급하게 가는 바람에 바지까지 두고 갈 뻔했지, 하하하...\n";
			link.l1 = "모르겠어, "+GetSexPhrase("아름다움","여보")+", 남자란 도대체 뭘까? 아내에게는 사창가에 '점검'하러 간다고 하고, 정부에게는 아내에게 급히 돌아간다고 했지만, 정작 그가 진심으로 원한 건 그 만을 순찰하는 일이었지. "+GetSexPhrase("하하하!..","하하하!")+"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;
		
		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";			
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "")
			{ 
				Locations[FindLocation(TargetLocation)].DisableEncounters = true;
				LAi_LocationDisableOfficersGen(TargetLocation, true);
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		// <-- генератор "A reason to hurry"
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = LinkRandPhrase("아니, 자기야, 미안하지만 안 돼. 기꺼이 도와주고 싶지만, 내가 할 수 없어.","아니, "+GetSexPhrase("잘생긴","아가씨")+", 나는 반지를 본 적 없어...","미안하지만, 아니오. 나는 반지를 본 적이 없어.");
				link.l1 = "안타깝군... 그래도 고맙다.";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "총독의 반지를 말하는 거야?";
					link.l1 = "그래, 자기야!";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("아니야, 자기야, 미안하지만 안 돼. 기꺼이 도와주고 싶지만, 할 수 없어.","아니, "+GetSexPhrase("잘생긴","아가씨")+", 나는 반지를 본 적 없어...","미안하지만, 아니오. 나는 반지를 본 적 없어.");
					link.l1 = "안타깝군... 그래도 고맙다.";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "미안하지만, 그 반지는 선물로 받은 것이기 때문에 돌려줄 의무가 없어.";
			link.l1 = "선물이라고?! 누가 준 거야?";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		
		case "TakeMayorsRing_S3":
			dialog.text = "물론 총독 본인이시지!";
			link.l1 = "하지만 그는... 최소한 말해도 취해 있었어. 아무것도 기억을 못 해.";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		
		case "TakeMayorsRing_S4":
			dialog.text = "그게 나랑 무슨 상관이야? 그 자가 취했으면 그건 자기 문제지, 내 문제가 아니야!";
			link.l1 = "정말 그 사람과 다툴 필요가 있나? 이건 결혼 반지야, 너도 알잖아... 그냥 돌려줘, 이런 작은 것 때문에 문제 생길 필요 없어.";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "좋아, 반지는 돌려주겠지만, 오천 페소는 내게 내야 해.";
				link.l1 = "좋아, 돈 가져가고 반지 내놔.";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "오, 그래. 놈한테 주게!";
				link.l1 = "그건 확실하지, 자기야!";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		
		case "TakeMayorsRing_S6":
			dialog.text = "여기 있어...";
			link.l1 = "좋아, 그럼. 도와줘서 고마워, 자기야.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
		
		//Jason --> Заносчивый аристократ
		case "Badboy":
			pchar.GenQuest.Badboy.Brothel.City = npchar.city; //город квестодателя
			//log_info(pchar.GenQuest.Badboy.Brothel.City); // patch-6
			pchar.GenQuest.Badboy.Brothel.nation = npchar.nation;
			pchar.GenQuest.Badboy.Brothel.Name = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "있지, 우리한테 골칫덩이 손님이 한 명 있어 - "+pchar.GenQuest.Badboy.Brothel.Name+". 그리고 그 자가 올 때마다 정말 우리를 짜증나게 해요! 처음엔 선술집에서 술에 취하고, 그다음엔 여기 와서 여자 하나 꼬셔서 난동을 피우죠\n제일 나쁜 건 그가 귀족 출신이라는 거예요! 우리 총독과 먼 친척이라서, 우리는 그 녀석의 온갖 행패를 참아야만 해요. 혹시 그 건방진 젊은이를... 음... 좀 진정시키거나, 내 업소에 다시는 오지 않게 해줄 수 있겠어요?";
			link.l1 = "총독의 친척이라고? 흠... 관헌들과 엮이고 싶지 않군. 정말 미안하다.";
			link.l1.go = "exit";
			link.l2 = "그렇게 해 줄 수 있을 것 같군. 어디서 그 망나니를 찾을 수 있는지 말해 봐.";
			link.l2.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "이 시간쯤이면 그는 보통 이미 선술집에 가 있지. 거기서 술에 취한 다음 이쪽으로 들르곤 해.";
			link.l1 = "알겠어. 뭐, 아마 거기서 그를 만나게 되겠지.";
			link.l1.go = "exit";
			//создаем дебошира
			int iRank, iType, b;
			string sBlade, sPistol;
			if (sti(pchar.rank) < 6) iType = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 16) iType = 1;
			if (sti(pchar.rank) >= 16) iType = 2;
			switch (iType)
			{
				case 0:
					iRank = 6;
					sBlade = "blade_12";
					sPistol = "pistol1";
					b = 25;
				break;
				case 1:
					iRank = sti(pchar.rank)+10;
					sBlade = "blade_09";
					sPistol = "pistol1";
					b = 65;
				break;
				case 2:
					iRank = sti(pchar.rank)+5;
					sBlade = "blade_14";
					sPistol = "pistol1";
					b = 40;
				break;
			}
			sld = GetCharacter(NPC_GenerateCharacter("Badboy", "citiz_"+(7+rand(1)), "man", "man", iRank, HOLLAND, -1, true, "citizen"));
			FantomMakeCoolFighter(sld, iRank, b, b, sBlade, sPistol, "bullet", makeint(iRank*5));
			sld.name = pchar.GenQuest.Badboy.Brothel.Name;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Badboy";
			sld.greeting = "noble_male"; // patch-6
			LAi_SetLoginTime(sld, 15, 22);
			LAi_SetSitType(sld);
			FreeSitLocator(pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit", "sit1");
			pchar.GenQuest.Badboy.Brothel.Type = iType; //запомним тип
			pchar.GenQuest.Badboy.Brothel = "true";
		break;
		
		case "Badboy_complete":
			dialog.text = "오, 자네 진짜 사내구나? 내가 늘 자네를 믿을 수 있다고 생각했지.";
			link.l1 = "이렇게 아름다운 숙녀분과 그녀의... 보호자들을 돕게 되어 언제나 기쁩니다.";
			link.l1.go = "Badboy_complete_1";
		break;
		
		case "Badboy_complete_1":
			dialog.text = "당신은 용감할 뿐만 아니라 정말 멋지군요. 특별한 방식으로 감사하고 싶어요. 오직 여자가 남자에게 할 수 있는 그런 방식으로요. 이건 절대 잊지 못할 거예요, 약속해요. 위층으로 올라오세요, 용감한 선원님...";
			link.l1 = "...";
			link.l1.go = "Badboy_complete_2";
		break;
		
		case "Badboy_complete_2":
			pchar.questTemp.different.HostessSex.city = pchar.GenQuest.Badboy.Brothel.City;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); 
			DialogExit();
			if (sti(pchar.GenQuest.Badboy.Brothel.Type) != 2)
			{
				DeleteAttribute(pchar, "GenQuest.Badboy");
			}
			else
			{
				pchar.quest.Badboy_Brothel.win_condition.l1 = "location";
				pchar.quest.Badboy_Brothel.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City +"_town";
				pchar.quest.Badboy_Brothel.function = "Badboy_friends";
				DeleteAttribute(pchar, "GenQuest.Badboy.Continue"); // patch-6
			}
			SaveCurrentQuestDateParam("questTemp.Badboy");
			if (!CheckAttribute(pchar, "questTemp.RomNaTroih"))
			{
				pchar.questTemp.RomNaTroih = true;
			}
		break;
		// <-- Заносчивый аристократ
		
		//Португалец
		case "Portugal":
			dialog.text = "나한테 돈을 좀 빚진 사람이 있는데... 뭐라고 말해야 할지 모르겠군...";
			link.l1 = "말이 필요 없어! 그 자를 찾아서 마지막 페소까지 다 털어내겠어, 오직 당신의 깊은 눈동자를 한 번 더 보기 위해서지! 이름만 말해 줘!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "아니, 아니요, 제 말을 잘못 이해하셨습니다, 선장님! 이 사람... 그에게 나쁜 짓은 하지 마세요. 그냥 빚이 있다는 것만 상기시켜 주십시오. 이름은 휴고 아벤델이고, 아마 가장 싼 술을 파는 곳 어디든 그를 찾을 수 있을 겁니다. 제발, 그에게 폭력은 쓰지 마세요!\n그냥... 그가 갚겠다고 약속했다는 것만 상기시켜 주세요. 경비를 끌어들이고 싶진 않지만, 장교들 중에 제 친구가 있으니, 제가 기다리고 있다고 전해 주시고, 그를 존중하는 마음에서 내일을 넘기지 않고 조치를 취할 수밖에 없다고 전해 주세요. 약속을 상기시켜 주시기만 하면 됩니다.";
			link.l1 = "당신의 말씀이 곧 제 법입니다, 마님. 기꺼이 부탁을 들어드리겠습니다.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			sld = InitHugo("Hugo","Avendell");
			FreeSitLocator("Marigo_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
			AddLandQuestMark(sld, "questmarkmain");
			SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
			pchar.questTemp.Portugal = "begin";
		break;
		
		case "Portugal_exit":
			dialog.text = "감사합니다, 선장님. 그가 신중하게 행동하길 진심으로 바랍니다.";
			link.l1 = "그 점은 확신합니다, 부인. 이제 물러가도록 하겠습니다.";
			link.l1.go = "exit";
			sld = characterFromId("Avendel");
			sld.lifeday = 0;
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "이런! 설마 그에게 무슨 끔찍한 짓을 한 건 아니겠지... 그 사람 돈 한 푼도 없었어, 나도 알고 있었지! 그냥 같은 작은 마을에서 자랐을 뿐이야, 내가 경비병들에게 알릴 리 없잖아! 그냥 좀 놀래켜 주고 싶었을 뿐이야... 술에 빠져서 완전히 망가지기 전에 정신 좀 차리게 하려고 했던 거야!";
			link.l1 = "흠... 그래도 여기 네 돈이다. 그리고 휴고는 걱정하지 마, 괜찮으니까... 적어도 술만 깨면 괜찮을 거야.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "아이고, 선장님, 잘 모르시겠지만! 그 사람은... 뭐, 아시잖아요, 현상금 사냥꾼이라고 불리는 자들이에요 - 용병들이죠, 해적이나 도둑을 쫓아다니며 없애버리는 놈들이요. 하지만 그 사람은, 솔직히 말해, 별로 운이 좋지 않았어요\n얼마 전, 결국 무리하게 돈을 쓰다가 선원들과 배를 다 잃었고, 그 뒤로는 날마다 술잔 바닥에서 허우적대고 있지요. 옛 친구 사이니까 가끔 여기 오게 해 주는 겁니다. 지금은 정말... 정말 불쌍한 신세가 됐어요. 한때는 라망슈 해안 우리 마을에서 제일 잘생긴 남자였는데, 지금 꼴 좀 보세요\n그가 뭔가 약속했다는 것도, 당신이 자기 돈을 썼다는 것도 알아요! 이 돈은 제가 드릴 테니, 제발 그 사람한테 나쁜 짓만은 하지 말아 주십시오, 선장님!";
			link.l1 = "좋아, 알겠소, 부인. 돈은 가지시오, 그대 것이오. 그리고 그대 친구에 대해서는, 해치지 않겠다고 약속하오. 이제 실례하겠소, 볼 일이 좀 있어서. 그리고 이렇게 아름다운 숙녀를 도울 수 있어 기뻤소.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_tavern_7";
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Portugal = "AvendelTavern";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "쉿, 목소리 낮춰... 마담 롤리타에게 나랑 데이트해 달라고 부탁해 줘. 그리고 위층으로 올라와, 거기서야 자유롭게 얘기할 수 있으니까. 그때까지는 아무 말도 하지 마... 이봐, 선원, 나 만지기 전에 마담한테 돈부터 내! (낄낄)";
			link.l1 = "가는 중이야, 자기야...";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
           DialogExit();
		   chrDisableReloadToLocation = false;
		   pchar.questTemp.Mtraxx = "jewelry_2";
		break;
		
		case "mtraxx_2":
			pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //снять таймер
            dialog.text = "아니, 나는 아니야. 내가 전부 다 얘기해 줄 테니, 끼어들지만 마.";
			link.l1 = "난 잘 듣고 있어!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "좋아. 약 일주일 전에 군함 한 척이 산토도밍고에 도착했어. 폭풍이나 전투 때문에 손상을 입어서 곧바로 수리가 시작됐고, 선원들은 요새로 옮겨졌지. 그런데 그 배의 선장은, 남는 시간 내내 바로 여기서 시간을 보냈어. 이틀 내내 술 마시고 쉬면서 우리 여자애 한 명과 함께 있었지. 바로 그 애가 보석을 받았어, 그것도 한두 개가 아니야. 그 애는 자랑을 끝없이 해댔지 – 롤리타는 손님이 준 선물은 우리가 가지게 해주거든.\n그 바보 같은 애는 그 선물의 진짜 가치를 전혀 몰랐지만, 나는 한눈에 알아봤지. 술에 취한 선장이 호박이 산더미처럼 쌓여 있다고 자랑했다는 얘기를 듣고, 나는 곧바로 타이렉스에게 편지를 보냈어...";
			link.l1 = "";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "선장이 다음에 도착할 때쯤 나는 모든 준비를 마쳐서, 그가 가장 좋아하는 여자가 다른 손님과 함께 있게 했고, 내가 그 '일'을 맡게 되었지. 나는 그에게서 좌표를 알아내려고 했지만, 아쉽게도 소용없었어. 그는 그저 자신이 크라수스만큼 부자가 되어 구세계로 돌아갈 거라고 자랑만 했지\n위치에 대해서는 한마디도 하지 않았어. 내가 알아낸 유일한 것은 그의 배가 수리되어 곧 아바나로 출항할 예정이고, 그곳에서 올바른 방향으로 임무를 잡으려고 한다는 거야. 어차피 그는 배의 소유주도 아니거든.";
			link.l1 = "그럼, 지금 그는 아바나에 있나?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "이틀 전에 새벽에 출항했어. 여기서 뱃사람은 너니까, 계산은 네가 해.";
			link.l1 = "선장의 이름, 배 종류와 이름, 뭐라도 아는 거 있나?";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = "뭐야, 나를 바보로 아나? 그의 이름은 에스베르도 카바냐스, 칸타브로의 선장이야. 선원들은 그 배를 스쿠너라고 부르던데.";
			link.l1 = "그게 전부라는 거야?";
			link.l1.go = "mtraxx_7";
		break;
		
		case "mtraxx_7":
            dialog.text = "더 뭘 원하지? 아마 아바나에 도착하기 전에 그를 따라잡을 수 있을 거야. 하지만 시간 낭비하지 마. 그자가 쿠바를 떠나 은닉처로 가기 전에 오래 머물 것 같진 않으니, 그땐 기회가 없어져. 다시 생각해보니, 한두 시간 정도는 머물러도 되겠군. 어쨌든 돈은 냈으니까.";
			link.l1 = "좋은 말이야, 자기야. 두 시간쯤이야 별 차이 없겠지...";
			// belamour legendary edition -->
			link.l1.go = "mtraxx_7S";
			link.l2 = "다음에 하자, 자네. 점심시간이라도 좀 가지게. 교회에 가든지, 아니면 다른 걸 하든지.";
			link.l2.go = "mtraxx_7NS";
			sTotalTemp = npchar.id;
			AddMapQuestMarkCity("Havana", false);
			AddLandQuestMark(characterFromId("Havana_PortMan"), "questmarkmain");
		break;
		
		case "mtraxx_7S":
            DialogExit();
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			AddDialogExitQuest("PlaySex_1");
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		
		case "mtraxx_7NS":
            DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			AddQuestRecord("Roger_1", "3");
			pchar.questTemp.Mtraxx = "jewelry_3";
			SetFunctionTimerCondition("Mtraxx_JewelryHavanaOver", 0, 0, 7, false); // таймер
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			pchar.quest.mtr_jewelry_havana.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_havana.win_condition.l1.location = "Cuba2";
			pchar.quest.mtr_jewelry_havana.function = "Mtraxx_HavanaInfo";
			DeleteAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor");
			DeleteAttribute(pchar, "questTemp.ZA.Block");
		break;
		// <-- legendary edition
		case "mtraxx_R":
            dialog.text = "오-오... 아쉽군. 난 자네가 휴가차 온 줄 알았지. 내 아가씨들이 용감한 코르세어들을 얼마나 그리워하는지 모른다네. 좋아, 말해봐, 무슨 일이지?..";
			link.l1 = "마르쿠스가 이틀 동안 당신네 술집에서 제대로 파티를 벌이고, 포도주를 다 마시고, 여자들도 다 품으라고 시켰어. 언제부터 시작할까?";
			link.l1.go = "mtraxx_R1";
		break;
		
		case "mtraxx_R1":
            dialog.text = "아, Charlie Prince, 너의 유머는 네 검만큼이나 날카롭구나! 거의 화낼 뻔했잖아... 얘들아! 손님이 오셨다, 아주 특별한 손님이야! 술과 음식을 가져와라!";
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = "여기 예쁜 아가씨들 전부 불러 와! 오늘은 쉬면서 신나게 놀 거야! 요호호!..";
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = "잠깐만 기다려, 자네트. 너랑 네 아가씨들에게 줄 금을 내 배에서 가져와야 해. 금방 돌아올게!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
				chrDisableReloadToLocation = false;
			}
		break;
		
		case "mtraxx_R2":
			AddMoneyToCharacter(pchar, -30000);
            dialog.text = "우리 손님들이 모두 당신처럼 다정하고 잘생기고 후했으면 좋겠네요... 완벽하게 쉬게 해드릴게요. 아가씨들!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
		// belamour ночной приключенец
		case "NA_Girl":
            dialog.text = "오, 여기 안목 있는 손님이 있구먼, 히히... 그래, 딱 맞는 아가씨가 있지. 하지만 값이 만만치 않아: "+makeint(pchar.GenQuest.NightAdventure_money)+" 페소입니다."; 
			link.l1 = "거래지.";
			link.l1.go = "NA_Girl_1";
		break;
		
		case "NA_Girl_1":
			AddMoneyToCharacter(pchar, -makeint(pchar.GenQuest.NightAdventure_money));
            dialog.text = "좋아, 자기야. 사랑의 여신 사제가 위층에서 기다리고 있을 거야. 믿어, 절대 후회하지 않을 거야."; 
			link.l1 = "나 이미 안 그래.";
			link.l1.go = "NA_Girl_2";
		break;
		
		case "NA_Girl_2":
			DialogExit();
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhore"; 
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_NobleWhore_7";
		break;
		// <-- приключенец
		
		case "chicken_god":
			dialog.text = "당신과 아귀에바나 나리를 위해서라면? 물론이지. 만 냥이네, 선장.";
			if (sti(pchar.money) >= 10000) {
				link.l1 = "잠깐, 그렇게 하면 안 돼!.. 젠장! 됐다, 여기 보수다.";
				link.l1.go = "chicken_god_pay";
			} else {
				link.l2 = "대출 받을 수 있을까?";
				link.l2.go = "chicken_god_notpay";
			}
		break;
		
		case "chicken_god_pay":
			dialog.text = "머무는 동안 즐거운 시간 되십시오, 선장님. 영업할 때 다시 찾아주시면 감사하겠습니다. 저희 업소는 신사 숙녀 여러분을 위한 다양한 오락거리를 제공합니다.";
			link.l1 = "...";
			link.l1.go = "chicken_god_pay_1";
		break;
		
		case "chicken_god_pay_1":
			dialog.text = "";
			link.l1 = "Madam "+npchar.name+", 여기서 무슨 일이 벌어지고 있는지라도 설명해 줄 수 있나? 총독은 네가 한 달 동안 원주민을 책임자로 두고 있었다는 걸 알기나 하나? 내가 단언컨대, 창관이 하루만 문을 닫아도 어떤 정착지도 버틸 수 없네!";
			link.l1.go = "chicken_god_pay_2";
		break;
		
		case "chicken_god_pay_2":
			dialog.text = "방은 선장님 차지입니다. 이제, 실례하겠습니다.";
			link.l1 = "매력적이군. 안녕히 가십시오, 부인.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_PayForRoom");
		break;
		
		case "chicken_god_notpay":
			dialog.text = "왜요, 주님, 왜요? 나가! 저리 가, 저리 가, 더는 못 참겠어! 이 망할 놈아!";
			link.l1 = "잘 됐군.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotPayForRoom");
		break;
		
		//-->> Sinistra Ром на троих
		case "RomNaTroih_1":
			dialog.text = "음... 나는 평소에 이런 일 잘 안 하는데... 하지만 당신을 위해서라면 한 번 해볼게. 오늘은 운이 좋은 날이야, 선장!";
			link.l1 = "가자!";
			link.l1.go = "exit";
			pchar.RomNaTroih_Shluha = npchar.id;
		break;
		
		case "RomNaTroih_2":
			dialog.text = "나는 너한테 화가 났다, 선장... 하지만 네가 충분히 노력한다면 자비를 베풀어 주겠다.";
			link.l1 = "그래, 그럴게. 와인 좀 따를까?";
			link.l1.go = "exit";
			Achievment_Set("ach_CL_105");
		break;
		//<<-- Sinistra Ром на троих
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse" && rCharacter.horse == "HorseStay")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}
