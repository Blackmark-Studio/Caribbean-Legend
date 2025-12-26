// Ричард Флитвуд - английский капитан
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "Start_main")
				{
					dialog.text = "안녕하십니까, 선장님! 내 겉모습에 신경 쓰지 마시오, 나는 괜찮소—거의 앞을 못 보지만, 그래도 괜찮소. 자기소개를 하지요: 나는 리처드 플리트우드요.";
					link.l1 = "안녕하십니까, 만나 뵙게 되어 반갑습니다. 저는 선장입니다 "+GetFullName(pchar)+".";
					link.l1.go = "First_Task";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
				{
					if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
					{
						dialog.text = "배를 정박하라고 했잖아. 내 말 듣기는 하는 거야?";
						link.l1 = "그래, 내가 맡아서 처리하지.";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "그래, 또 왔군. '발키리'의 지휘를 맡으라. 내 선원들에게는 이미 자세한 내용을 전달해 두었으니, 브리지타운으로 항해하게. 도시의 모든 주요 인물들을 만나 우리가 논의한 소문을 퍼뜨리게. 그리고 그 자식이 공격해 올 때를 대비하라. 배를 바꾸거나 함대를 꾸리면 놈이 함정을 의심하고 나타나지 않을 테니 절대 그러지 마라\n놈의 배에 반드시 승선하여 세인트 존스로 가져가야 한다. 해적의 항해일지를 꼭 찾아내야 한다. 그것만이 루카스 로덴부르크가 연루된 유일한 증거가 될 것이니. 자네라면 잘 해낼 거라 믿네. 행운을 빈다, 선장.";
						link.l1 = "감사합니다! 약속한 대로 일을 처리하겠습니다.";
						link.l1.go = "First_Task_3";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
					}
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "MirageTake")//а вот теперь начинается перебор кораблей
				{
					pchar.quest.ToAntiguaMirageOver.over = "yes"; //снять таймер
					int iMir = 0;
					int iVal = 0;
					for(i = 0; i < COMPANION_MAX; i++)
					{
						iTemp = GetCompanionIndex(PChar, i);
						if(iTemp > 0)
						{
							sld = GetCharacter(iTemp);
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
							{
							iMir = 1;
							RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;//чистый корпус
							SetShipSailsFromFile(sld, "ships/parus_silk.tga");
							SetSailsColor(sld, 0);//белый хлопковый парус
							DeleteAttribute(sld, "ship.sails");//починить паруса
							DeleteAttribute(sld, "ship.masts");//вернуть мачты
							}
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
						}
					}//установили признак наличия кораблей в эскадре.
					if (iMir == 1 && iVal == 0)//потеряли Валькирию
					{
						dialog.text = "돌아오셨군요, 선장님... 이미 당신의 항해에 대해 모두 들었습니다.";
						link.l1 = "정말인가? 그렇다면 너도 알겠군...";
						link.l1.go = "Fleetwood_lostVal";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 1)//потеряли Мираж
					{
						dialog.text = "돌아오셨군요, 선장님... 이미 당신의 항해에 대해 모두 들었습니다.";
						link.l1 = "정말인가? 그렇다면 너도 알겠군...";
						link.l1.go = "Fleetwood_lostMir";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 0)//а это вообще плохо
					{
						dialog.text = "돌아오셨군요, 선장님... 이미 당신의 항해에 대해 모두 들었습니다.";
						link.l1 = "그래? 그렇다면 너도 알겠군...";
						link.l1.go = "Fleetwood_lostFull";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
						dialog.text = "돌아오셨군요, 선장님... 이미 당신의 항해에 대해 모두 들었습니다.";
						link.l1 = "정말인가? 그렇다면 너도 알겠군...";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "toAntigua")
				{
					dialog.text = "안녕하시오, 친구! 다시 만나 반갑소! 자네 배에 아비게일이 있소?";
					link.l1 = "유감이지만, 나는 몰라, 리처드. 그녀는 나와 함께 가기를 거부했어. 이미 가진 돈을 모두 잃은 아버지에게 그녀의 떠남이 큰 상처가 될 거라서. 그래서 내가 직접 문제를 해결하기로 했고, 솔로몬의 돈과 그 섬을 찾아보기로 결심했지...";
					link.l1.go = "Fleetwood_LastTask";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				dialog.text = "더 필요한 거 있습니까, 선장님?";
				link.l1 = "아니, 난 이미 떠나려고.";
				link.l1.go = "exit";		
				NextDiag.TempNode = "First time";
			}
				dialog.text = "또 필요한 거 있소, 선장?";
				link.l1 = "아니, 나는 이미 떠나려 한다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fleetwood_abordage":
			PlaySound("Voice\English\hambit\Richard Flitwood-03.wav");
			dialog.text = "제기랄 해적 놈! 네가 백병전을 이겼을지라도, 나는 내 임무를 끝까지 다할 것이다. 나는 이미 화약고에 불을 붙이도록 준비해 두었다. 곧 내 배가 네 '유령선'과 함께 폭발할 거다. 너 따위가 다시는 영국 배 한 척도 침몰시키지 못할 거다. 나는 명예롭게 죽겠다!";
			link.l1 = "실망시켜서 미안하지만, 플리트우드, 네가 틀렸어. 내 배에는 해적이 없어; 전에 다 처리했지. 내가 네가 필요했고, 이 배는 완벽한 함정이었어.\n쓸데없는 인사는 그만두자. 이제 널 죽이고 네 불타는 배에서 벗어나야겠어!";
			link.l1.go = "Fleetwood_abordage_1";
		break;
		
		case "Fleetwood_abordage_1":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.HWIC.Holl = "FleetwoodCapture";
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "First_Task":
			dialog.text = "찰리에게서 이미 적의 무역 행렬을 성공적으로 가로챈 이야기를 들었소. 만나서 반갑소; 영국에는 이런 용감한 선장이 필요하오. 이제 아주 중요한 이야기를 해주겠소.";
			link.l1 = "듣고 있소, 플리트우드 나리.";
			link.l1.go = "First_Task_1";			
		break;
		
		case "First_Task_1":
			dialog.text = "해적 한 놈이 군도 전역에서 폭력을 저지르며, 전설의 유령선 '플라잉 더치맨'을 사칭하고 있소. 그자는 전설의 유령선 '플라잉 더치맨' 행세를 하고 있지. 내 생각엔 분명히 네덜란드 놈이지만, 하늘을 나는 건 아니오. 나는 이 자가 네덜란드 서인도 회사의 부국장 루카스 로덴부르크의 용병이라고 믿는 편이오.\n로덴부르크는 영국을 상대로 은밀한 무역 전쟁을 선포했소. 이 '유령선'은 오직 영국 국기를 단 상선만을 공격하지. 진짜 전쟁 없이 이 지역에서 우리의 영향력을 약화시키는 것이 회사에 매우 중요하오.\n나는 한동안 이 유령선을 쫓아왔지만, 그 선장은 매우 노련한 항해사이고 배도 빠르고 잡히지 않소.\n공개 전투로는 그 자칼을 잡는 게 불가능하니, 우리도 교묘하게 움직여야 하오. 그리고 최근 내 목숨을 노린 사건이 우리에게 큰 도움이 될 것이오. 어떻게 생각하시오, 선장? 두렵소?";
			link.l1 = "절대 안 돼. 저 자식을 찾아내서 침몰시키는 데 기꺼이 도와주겠소. 그걸 부탁하려던 거였지, 맞지?";
			link.l1.go = "First_Task_2";	
		break;
		
		case "First_Task_2":
			dialog.text = "옳소. 이제 세부 사항을 논의합시다. 내 부하들이 내가 병상에 누워 죽어가며 내 배 '발키리'를 그대에게 팔았다는 소문을 퍼뜨릴 것이오. 다음으로, 우리 작은 속임수를 실행할 것이오. 그대는 내게서 브리그를 사서 대부분의 대포를 없앤 상인인 척해야 하오.\n그러니 그대 임무는 바베이도스로 항해해, 그곳 모두에게 선창이 귀중한 화물로 가득하고 주머니엔 돈이 넘쳐난다고 알리는 것이오. 곧 출항할 계획이라고도 말하시오. 욕심 많고 단순하지만 부유한 상인 역할을 제대로 해내시오.\n저 빌어먹을 네덜란드인은 브리지타운에서 무역선 정보를 얻는다오. 누가 그에게 정보를 주는지는 알 수 없소. 현지 상인부터 총독까지 모두가 의심받고 있소, 특히 총독이라면 정말 끔찍한 일이지.\n내 '발키리'와 그 선원들을 지휘하시오. 하지만 먼저, 그대의 모든 배는 여기 두고 가야 하오. 이미 항만 관리인과 얘기해 두었소. 기함 한 척당 한 달에 만 페소가 들 것이오.\n모든 준비가 끝나면 내게 돌아오시오. 내가 후속 조치를 취하겠소. 아, 선장, 은화 수송대를 잡은 몫과 항만 관리인에게 줄 만 페소 챙기는 것 잊지 마시오—돈은 서랍장에 있소.";
			link.l1 = "알겠습니다, 플리트우드 나리. 항만장에게 가보겠습니다.";
			link.l1.go = "exit";	
			pchar.questTemp.HWIC.Eng = "GotoPortoffice";
			bDisableFastReload = false;//откроем быстрый переход
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			AddLandQuestMark(characterFromId("SentJons_PortMan"), "questmarkmain");
		break;
		
		case "First_Task_3":
			DialogExit();
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.EngEquip = "true"; //форма солдат
			pchar.questTemp.HWIC.Eng = "GotoBridgetown";
			GetValckiriaToCharacter(pchar);
			pchar.quest.Knippel_Officer.win_condition.l1 = "location";
			pchar.quest.Knippel_Officer.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Knippel_Officer.function = "KnippelToOfficer";
			pchar.questTemp.HWIC.Eng.BridgeCounter = 0;//счетчик посещений неписей Бриджтауна по квесту
			AddQuestRecord("Holl_Gambit", "2-5");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_shipyarder"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Mayor"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_usurer"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_PortMan"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Hostess"), "questmarkmain");
		break;
		
		//изымаем корабль
		case "Fleetwood_lostMir":
			dialog.text = "그래, 자네가 해적선을 잡는 임무에 실패했다는 것 알고 있네. 내 모든 계획이 망가졌어. '발키리'는 내가 가져가겠네. 이제 가도 좋네, 더 이상 자네의 도움이 필요 없네.";
			link.l1 = "정말 유감이오. 안녕히 계십시오, 플리트우드 나리.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;
		
		case "Fleetwood_lostVal":
			dialog.text = "그래, 네가 '발키리'를 잃어버린 것 알고 있다네. 정말 용납할 수 없는 일이었지... 내가 나포한 해적선을 가져가겠네. 이제 가도 좋다네, 자네의 도움이 더는 필요 없네.";
			link.l1 = "정말 유감이오. 안녕히 계시오, 플리트우드 나리.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;
		
		case "Fleetwood_lostFull":
			dialog.text = "그래, 자네가 보기 드문 얼간이에다 실수투성이라는 것쯤은 알고 있지. 해적선을 잡지도 못하고 내 '발키리'까지 잃었잖아. 정말 실망이 크군. 나가!";
			link.l1 = "정말 유감이오. 안녕히 계시오, 플리트우드 나리.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Книппеля из офицеров
			sld = characterFromId("Knippel");
			ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_complete":
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");	
			if (CheckCharacterItem(pchar, "JacobJournal"))//проверяем журнал
			{
				dialog.text = "그래, 자네가 우리 계획을 성공시킨 것 알고 있네. 악랄한 해적을 처치하고 그의 배도 손에 넣었다지. 그 배의 진짜 이름이 무엇인가?";
				link.l1 = "Mirage";
				link.l1.go = "Abigile";
			}
			else//нет журнала - нет продолжения квеста
			{
				dialog.text = "그래, 우리 계획이 성공했다는 것 알고 있네. 자네가 그 악랄한 해적을 처치하고 그의 배도 손에 넣었지. 내 '발키리'는 내가 다시 가져가겠네. 해적선은 전리품으로 자네가 가져도 되네. 일종의... 보상이라고 생각하게. 부두에서 불이 번지면서 자네가 항구에 정박해둔 배는 전소되고 말았네. 불편을 끼쳐 미안하네,\n "+pchar.name+"... 유령선이 당신에게 더 잘 봉사하길 바라오.\n새 배의 끈질긴 때와 해초를 깨끗이 치우라고 명령해 두었소. 또한 당신의 아름다운 배에 최고급 면으로 만든 새 돛도 달아줄 것이오.\n마지막으로, 10만 페소의 보상과 이 항해 도구를 받아주시오. 나는 언제나 이것을 진정한 선원에게 주고 싶었는데, 당신이 훌륭히 해냈으니 마땅하다 생각하오! 자, 이제 작별을 고할 시간이로군. 나는 여기서 할 일을 마쳤으니 유럽으로 돌아가야 하오. 행운을 빌겠소, 선장!";
				link.l1 = "리처드, 너도 마찬가지야!";
				link.l1.go = "exit";
				LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//закроем Флитвуда в комнате и пусть там сидит
				pchar.questTemp.HWIC.Eng = "end";
				pchar.questTemp.HWIC.Detector = "eng_win_half";
				CloseQuestHeader("Holl_Gambit");
			}
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "bussol");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			AddSimpleRumourCity("They say that you and Richard Fleetwood has planned some military operation and you have personally destroyed that elusive pirate who has been robbing our trade ships. You are a real hero, captain!", "SentJons", 20, 3, "");
		break;
		
		case "Abigile":
			dialog.text = "신기루? 아주 어울리는 이름이군... 나는 내 '발키리'를 너에게서 되찾을 거다. 그러니 해적선은 전리품으로 가져도 된다. 일종의 보상이라고 생각해라. 항구에 정박해 있던 네 배는 부두에서 시작된 불이 번지면서 불타버렸어. 유감이다, \n "+pchar.name+"... 유령선이 자네에게 더 잘 봉사해주길 바라네.\n새 배의 끈질긴 때와 해초는 전부 깨끗이 치우라고 명령해 두었네. 또 최고의 면으로 만든 새 돛도 달아줄 것이네, 자네의 아름다운 배에 말이야.\n마지막으로, 10만 페소의 보상금과 이 항해 도구를 받아주게. 나는 늘 이걸 쓸모 있는 선원에게 넘겨주고 싶었지... 자네는 훌륭히 해냈고, 나는 자네가 자랑스럽네! 그 자식의 항해일지는 가지고 있나?";
			link.l1 = "예, 물론이지. 여기 있어, 가져가. 묻고 싶은 게 있는데, 혹시 루카스 로덴부르크의 부하들 중에... 아시아인이 있나?";
			link.l1.go = "Abigile_1";			
		break;
		
		case "Abigile_1":
			RemoveItems(PChar, "JacobJournal", 1);
			dialog.text = "그래, 있어. 중국인 롱웨이, 자기 배 '메이펑'의 선장이야. 해적의 기록에서 그걸 읽었나? 한번 보자...(읽으며) 오, 역시. 예상대로 루카스 로덴부르크가 이 모든 일의 배후였군! 뭐, 어쨌든 지금은 우리 일이 아니야... 우리 총독께서 저 자식 처리하실 거다. 루카스 로덴부르크는 자기 짓거리에 대한 책임을 져야 할 거야!";
			link.l1 = "흠, 흥미로운데, 영국 총독이 어떻게 네덜란드 신민을 '처리'할 수 있겠소?";
			link.l1.go = "Abigile_2";			
		break;
		
		case "Abigile_2":
			dialog.text = "정치적인 술수는 언제나 있기 마련이지, 내 친애하는 친구여... 네덜란드는 영국과의 무역 전쟁을 자신들이 시작했다고 인정해야 할 거야. 하지만 그럴 가능성은 적지. 대신 모든 책임을 로덴부르크에게 뒤집어씌우겠지. 루카스는 자리에서 물러날 수도 있고, 아닐 수도 있네. 어느 쪽이든 그의 경력에는 큰 타격이 갈 거야.\n하지만, 이건 지금 우리 일이 아니네, 선장. 자네는 맡은 바 임무를 훌륭히 해냈어. 그래서 자네에게 또 하나 아주 민감한 일을 맡기고 싶네.";
			link.l1 = "듣고 있네, 리처드. 이번에는 영국 왕관의 다음 희생양이 누구인가?";
			link.l1.go = "Abigile_3";			
		break;
		
		case "Abigile_3":
			dialog.text = "아니, 이번에는 좀 더 개인적이고 평화로운 일을 부탁하고 싶소. 짧은 이야기를 하나 들려주겠소. 그런데 그 이야기가 바로 자네의 '미라주'와 관련되어 있네.";
			link.l1 = "계속해.";
			link.l1.go = "Abigile_4";			
		break;
		
		case "Abigile_4":
			dialog.text = "한 달 전에 자네와 만나기 전에 나는 습격에 나서서 유령선을 쫓고 있었네. 마르티니크 남쪽, 동경 64° 41' 근처였지. 어디선가 싸움 소리가 들렸지만, 바람이 너무 약해서 제때 도착하지 못했네. 영국 플루트선이 지도에도 표시되지 않은 작은 섬 근처에서 유령선에 의해 침몰당했지\n나는 해적을 잡는 데 실패했고, 혹시라도 생존자가 있을까 싶어 그 섬에 들르기로 했네. 그리고 정말로 생존자를 찾았지. 유대인 난민 부녀였네. 딸의 이름은 아비가일이었고, 정말 아름다웠지! 살아 있는 기적이었어... 나는 그들을 배에 태워 퀴라소까지 데려다 주었지만, 그녀의 아버지 솔로몬은 나에게 별다른 호의를 보이지 않았네\n내가 이해한 바로는, 그 노인은 내가 그들의 배를 침몰시킨 해적이라고 생각했던 것 같네. 배에 대해 잘 알지도 못했고, 종류의 차이도 몰랐지. 그 짧은 항해 동안 아비가일과 나는 친구가 되었고, 솔직히 말하면 서로 사랑에 빠졌네. 멋진 이야기 아닌가?\n그런데 최근에 그 자식 로덴부르크가 내 아비가일에게 한동안 구애하고 있었다는 걸 알게 되었네, 생각이나 해보게! 나는 그녀의 아버지가 잃어버린 돈 문제만 해결되면 그녀를 이곳에 데려오려고 했었지. 그가 가진 모든 돈을 내가 말한 그 섬에 숨겨두었거든. 하지만 나는 그 위치를 찾지 못했네. 더는 기다릴 수가 없어\n아직 건강이 허락지 않아 직접 항해할 수 없으니, 자네가 빌렘스타트에 가서 아비가일을 찾아 이곳으로 데려와 주게. 내 이름을 말하면 그녀가 자네를 믿을 걸세.";
			link.l1 = "이 일에는 아무런 문제가 없어 보여. 지금 바로 출항할 준비가 되어 있네.";
			link.l1.go = "Abigile_5";			
		break;
		
		case "Abigile_5":
			PlaySound("Voice\English\hambit\Richard Flitwood-02.wav");
			dialog.text = "훌륭하군! 자네를 믿을 수 있어 기쁘네, "+pchar.name+". 네 일은 충분히 보상받을 테니, 그 점은 걱정하지 마시오.";
			link.l1 = "너무 오래 기다리게 하지 않겠네. 곧 보세, 리처드!";
			link.l1.go = "Abigile_6";			
		break;
		
		case "Abigile_6":
			DialogExit();
			npchar.greeting = "fleetwood_2";
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload2", true);//закроем спальню Аби
			AddQuestRecord("Holl_Gambit", "2-16");
			pchar.questTemp.HWIC.Eng = "toAbigile";
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			sld.greeting = "barmen_1";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Fleetwood_LastTask":
			dialog.text = ""+pchar.name+", 정말로 그 섬을 찾기로 결심한 건가? 너의 관대함에 감탄했어. 찾았나?";
			link.l1 = "그래, 맞아. 불행하게도 여기서부터 나쁜 소식이 시작되지. 간신히 그 저주받은 곳에서 살아 나왔어... 아직도 생각만 하면 몸이 떨린다니까...";
			link.l1.go = "Fleetwood_LastTask_1";
		break;
		
		case "Fleetwood_LastTask_1":
			dialog.text = "거기서 무슨 일이 있었나? 말해 주게, 친구여, 애태우지 말고!";
			link.l1 = "나는 섬에 도착해서 솔로몬이 분명히 상자를 숨겨두었을 만한 동굴로 향했다.\n정말 그곳에 상자가 있었다.\n하지만 내가 상자를 만지자 알 수 없는 힘이 나를 뒤로 내던졌다.\n폭발음이 들렸고, 나는 상자에서 열 걸음쯤 떨어진 곳에 내동댕이쳐졌다...";
			link.l1.go = "Fleetwood_LastTask_2";
		break;
		
		case "Fleetwood_LastTask_2":
			dialog.text = "믿을 수가 없군!";
			link.l1 = "간신히 살아남았어 - 여기저기 아프게 긁혔지. 정신을 차리려는데 머릿속에서 무서운 소리가 윙윙거리고, 끔찍한 괴물이 땅에서 바로 튀어나왔어... 오, 신이시여, 그 괴물!";
			link.l1.go = "Fleetwood_LastTask_3";
		break;
		
		case "Fleetwood_LastTask_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "리처드, 나는 미친 게 아니야. 정말로 있었던 일이야, 나조차도 믿기 힘들지만. 완전히 말라붙고 칠해진 인디언 시체였어, 머리에는 깃털 다발도 있었고. 그 괴물이 뭔가 중얼거리더니, 거대한 인디언 곤봉을 꺼내서 나를 공격했어!";
			link.l1.go = "Fleetwood_LastTask_4";
		break;
		
		case "Fleetwood_LastTask_4":
			dialog.text = "";
			link.l1 = "오, 맙소사... 아직도 내가 어떻게 그 괴물을 상대할 수 있었는지 이해가 안 돼... 수십 번이나 찔렀는데, 그 정도면 열두 명은 죽고도 남을 텐데도 버티더군... 숨을 돌린 뒤에야 그 불운한 상자를 열었지... 돈은 없었지만, 안에 다른 게 있었어. 한번 봐, 정말 흥미로운 물건이야!\n";
			link.l1.go = "Fleetwood_LastTask_5";
		break;
		
		case "Fleetwood_LastTask_5":
			RemoveItems(PChar, "GastonHead", 1);
			dialog.text = "으으... 끔찍하군..."+pchar.name+", 잠깐만... 분명 저놈이야! 나를 죽이려고 고추가루로 눈을 멀게 하던 그 자식의 대가리잖아!";
			link.l1 = "그를 아시오? 이름은 가스통, 브리지타운의 술집 주인이자 유령선 선장 반 베르크의 지지자요. 나는 그를 바로 알아봤지만, 누가 그를 죽였는지, 그리고 잘린 머리가 어떻게 그 이름 모를 섬의 솔로몬 상자에 들어가게 됐는지는 모르겠소!";
			link.l1.go = "Fleetwood_LastTask_6";
		break;
		
		case "Fleetwood_LastTask_6":
			dialog.text = "맞아요, 정말 으스스하고 알 수 없는 이야기군요. 신비롭기도 하고...";
			link.l1 = "정확히 그렇소. 돈이 사라졌으니 아비게일에게 돌아갈 이유가 없었지. 그래서 이 사실을 전하려고 여기 온 것이오. 어쩌면 리처드, 자네라면 이 엉망진창을 이해할 수 있을지도 모르겠군...";
			link.l1.go = "Fleetwood_LastTask_7";
		break;
		
		case "Fleetwood_LastTask_7":
			dialog.text = "나? 나도 여기서 아무것도 모르겠어, 너처럼... 하지만 한 가지는 확실히 말할 수 있어 – 이 일, 왠지 불길한 느낌이 들어..."+pchar.name+", 지금 내 말 잘 들어. 브리지타운에 가서... 가스통이 정말로 사라졌는지 확인하고 오게. 그리고 20일 뒤에 큐라소의 블랑카 석호로 오게. 찰리 크니펠이 거기서 자네를 기다릴 걸세. 나는 아비가일 아버지에게 줄 돈을 모을 것이고, 그 돈을 찰리에게 줄 테니 자네가 솔로몬에게 가져가서 아비가일을 앤티가로 데려가게. 이번에는 방해가 없을 테니, 반드시 이해하게. 가게, 친구!\n";
			link.l1 = "좋소, 리처드. 즉시 출항하겠소.";
			link.l1.go = "Fleetwood_LastTask_8";
		break;
		
		case "Fleetwood_LastTask_8":
			DialogExit();
			pchar.questTemp.HWIC.Eng = "toBarbados";
			AddQuestRecord("Holl_Gambit", "2-21");
			SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);//чтобы не тянули
			AddSimpleRumourCity("Oh, captain, I have heard that Richard Fleetwood really admires you. Trust me, his praise costs a lot. You must be a very important person...", "SentJons", 20, 3, "");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		break;
		
//---------------------------------------------против всех-----------------------------------------------
		
		case "InTerksShore":
			DelLandQuestMark(npchar);
			pchar.quest.Fleetwood_ShoreOver.over = "yes";//снять таймер
			dialog.text = "네가 내 아비게일을 납치한 그 잡놈이겠지. 찰리도 내게 돌아오지 않았으니, 그것도 네 짓임에 틀림없다.";
			link.l1 = "옳으십니다, 플리트우드 나리. 바로 접니다. 찰리가 당신께서 아비게일에게 써주신 편지 덕분에 제가 그녀의 신임을 얻도록 도와주었지요. 하지만 본론으로 들어가죠... 돈은 가져오셨습니까?";
			link.l1.go = "InTerksShore_1";
		break;
		
		case "InTerksShore_1":
			dialog.text = "그렇소. 하지만 먼저 아비게일을 보고 싶소. 그녀가 살아 있고 다치지 않았다는 걸 직접 확인해야 하오. 사생아의 말만 믿을 수는 없으니.";
			link.l1 = "나리, 지금은 조건을 내세울 처지가 아니라고 생각하지 않으십니까?";
			link.l1.go = "InTerksShore_2";
			// belamour legendary edition -->
			link.l2 = "이제 이 게임 더 이상 하고 싶지 않아. 아비는 나랑 같이 있을 거고, 넌 이 해변에 갇힌 거야! 쏴라!";
			link.l2.go = "InTerksShore_2a";
		break;

		case "InTerksShore_2a"://массовая драка на необитаемом острове
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;

		case "InTerksShore_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "그건 이해하지만, 나도 바보는 아니야. 아비게일을 보기 전엔 돈 이야기는 없다. 그래서 뭐? 기다리고 있잖아.";
			link.l1 = "좋소. 이제 패를 공개할 때가 되었군, 플리트우드 선장. 내가 여기서 만남을 주선한 건 돈 때문이 아니오. 뭐, 물론 돈도 받고 싶긴 하지만, 그보다 먼저 자네가 필요하오.";
			link.l1.go = "InTerksShore_3";
		break;
		
		case "InTerksShore_3":
			dialog.text = "나라고? 점점 더 흥미로워지는군... 이제야 이곳에서 무슨 일이 벌어지고 있는지 진짜로 알 것 같아. 말해 봐, 아비게일은 살아 있나? 그녀가 아직 숨 쉬고 있나, 아니면 네가 죽였나, 이 자식아?";
			link.l1 = "그녀의 운명에 대해선 모른 채 두는 게 좋겠군. 네가 알아야 할 건 단 하나, 그녀는 여기 없다는 것뿐이야. 그녀는 자기 역할을 훌륭히 해냈고, 이제 네 운명은 내 손에 달렸지. 사랑이란 참으로 멋진 것이야... 여우를 굴 밖으로 유인하려면 이 방법밖에 더 있겠나? 하하하!";
			link.l1.go = "InTerksShore_4";
		break;
		
		case "InTerksShore_4":
			dialog.text = "아직 그렇게 좋아하지 마라, 이놈아. 내가 이 섬에서 너를 위해 멋진 환영을 준비해 뒀으니, 누가 진짜 주인인지 아직 모를 거다! 그러니 각오해라, 나한테 할 말이 많을 테니 – 아비게일에 대해, 찰리에 대해. 네가 그들을 다치게 한 대가를 치르게 될 거다!";
			link.l1 = "나는 벌써 두려움에 떨고 있다! 이제 대화는 끝내자, 나리. 지옥 갈 준비나 해라, 천국엔 네 자리가 없으니.";
			link.l1.go = "InTerksShore_5";
		break;
		
		case "InTerksShore_5"://массовая драка на необитаемом острове
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
