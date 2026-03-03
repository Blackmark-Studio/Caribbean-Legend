// диалог протекторов, солдат и мушкетеров кланов LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "뭐 원하는 거야?";
			link.l1 = "아니, 아무것도 아니야.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- фразы гардов нарвалов --------------------------------------------
		// пост нарвалов на проход на Сан-Габриэль
		case "Narval_warning":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("이봐, 조심해라, 미친놈이 있다! 무장해!","적이 여기 있다! 무기를 들어라!","이 자식아! 이제 제대로 맛 좀 보여주지!");
				link.l1 = "젠장!";
				link.l1.go = "check_parol_fight";
				break;
			}
			ref location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "멈춰, 이봐. 앞은 나르발 구역이야, 낯선 놈 출입 금지다. 초대장이 있어야만 통과할 수 있어. 암호 알아?";
					link.l1 = "그래.";
					link.l1.go = "Narval_warning_yes";
					link.l2 = "아니.";
					link.l2.go = "Narval_warning_no";
				}
				else // если друг нарвалам
				{
					dialog.text = "아-아, "+GetFullName(pchar)+"! 이봐, 친구, 네가 여기서 자유롭게 돌아다녀도 된다고 들었어. 환영한다!";
					link.l1 = "고맙다, 친구!";
					link.l1.go = "exit";
				}
				location.nrv_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "암호를 잊지 않았길 바라는데...";
					link.l1 = "걱정하지 마...";
					link.l1.go = "exit";
				}
				else // если друг нарвалам
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! 어떻게 지내?";
					link.l1 = "괜찮아, 고마워!";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_warning_yes":
			dialog.text = "그럼 저기 있는 터프한 놈한테 가서 직접 말해봐. 걔한테 사기 칠 생각 하지 마, 우리 머스킷 든 녀석들이 뭘 해야 할지 잘 아니까. 만약 꼼수 부릴 생각이면, 그냥 돌아서 떠나는 게 좋을 거다. 지금 당장. 경고했으니까.";
			link.l1 = "좋아, 친구. 알겠어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_no":
			dialog.text = "그럼 여기서 할 일 없겠군, 물론 죽으러 온 게 아니라면 말이지. 아니면 그냥 농담하는 건가, 응? 나한테 장난치는 거야? 사실, 상관없어. 내려가. 내 일은 경고하는 거지 막는 게 아니니까. 암호를 모르면 돌아올 수 없을 거야.";
			link.l1 = "알겠어, 친구.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "뭐 더 필요한 거 있어? '산 가브리엘'로 내려가든가, 아니면 꺼져!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "미안하오, "+pchar.name+", 하지만 나는 근무 중이야. 귀찮게 하지 마, 친구. 어서 가!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_parol":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("이봐, 조심해라, 저 미친놈이다! 무기 들어!","적이 여기 있다! 무기를 들어라!","이 자식아! 이제 제대로 맛 좀 보여주지!");
				link.l1 = "젠장!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "미안하오, "+pchar.name+", 하지만 나는 근무 중이야. 귀찮게 하지 마, 친구. 어서 가!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol";
				break;
			}
			dialog.text = "거기 그대로 서 있어! 너 우리 중 한 명 아니잖아!";
			link.l1 = "서 있어, 서 있어.";	
			link.l1.go = "check_parol";
		break;
		
		case "check_parol":
			dialog.text = "암호를 말해, 분명하고 크게.";
			sTotalTemp = sNrvParol;
			if (CheckAttribute(pchar, "questTemp.LSC.NParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_" + (281 + rand(11)));
				link.l1.go = "check_parol_wrong";
				link.l2 = StringFromKey("QuestsUtilite_" + (293 + rand(11)));
				link.l2.go = "check_parol_wrong";
				link.l3 = StringFromKey("QuestsUtilite_" + (305 + rand(11)));
				link.l3.go = "check_parol_wrong";
				link.l4 = StringFromKey("QuestsUtilite_" + (317 + rand(11)));
				link.l4.go = "check_parol_wrong";
				
				switch (rand(3))
				{
					case 0:
						link.l1 = sTotalTemp;
						link.l1.go = "check_parol_1";
					break;

					case 1:
						link.l2 = sTotalTemp;
						link.l2.go = "check_parol_1";
					break;

					case 2:
						link.l3 = sTotalTemp;
						link.l3.go = "check_parol_1";
					break;

					case 3:
						link.l4 = sTotalTemp;
						link.l4.go = "check_parol_1";
					break;
				}
			}
			else
			{
				link.l1 = "암호? 비켜, 안 그러면...";
				link.l1.go = "check_parol_wrong";
			}
		break;
		
		case "check_parol_1":
			dialog.text = "좋아, 가도 된다.";
			link.l1 = "고마워, 친구...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			pchar.questTemp.LSC.parol_nrv = "true";
		break;
		
		case "check_parol_wrong":
			dialog.text = "흠... 이봐, 녀석들! 손님이 왔어!";
			link.l1 = "젠장!";
			link.l1.go = "check_parol_fight";
		break;
		
		case "check_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Narval_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("이봐, 조심해라, 저 미친놈이야! 무장해!","적이 여기 있다! 무기를 들어라!","이 자식아! 이제 제대로 맛 좀 보게 해주지!");
				link.l1 = "젠장!";
				link.l1.go = "check_parol_fight";
				break;
			}
			dialog.text = "비켜! 여기 서 있지 말고 가!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;
		
		// у резиденции
		case "Narval_residence":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("이봐, 조심해라, 저 미친놈이다! 무장해!","적이 여기 있다! 무기를 들어라!","이 자식아! 이제 우리가 제대로 맛 좀 보여주지!");
				link.l1 = "젠장!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // диалог от времени суток. лесник
			    {
					dialog.text = TimeGreeting()+", "+pchar.name+"! 문이 열려 있으니, 보스 보고 싶으면 들어가.";
					link.l1 = "좋아...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else
				{
                    dialog.text = TimeGreeting()+", "+pchar.name+"! 두목을 보고 싶으면, 지금은 자고 있어. 아침에 다시 와.";
					link.l1 = "좋아...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");	
                }					
				break;	
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "흑인들과 친구인 자들은 여기서 용납되지 않아. 두목의 직접 명령이야!";
				if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
				{
					link.l1 = "그가 나를 만나야 할 거야. 너희, 진짜 큰일 났다. 나는 제독의 공식 명령을 받고 여기 왔다. 그러니 젠장, 문 열어!";
					link.l1.go = "negotiations";
				}
				else
				{
				link.l1 = "나도 그를 보고 싶다고는 할 수 없지...";
				link.l1.go = "exit";
				}
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "두목을 보고 싶어? 흠, 그럼 지나가.";
			link.l1 = "...하게 해줘서 고마워.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else
			{
            dialog.text = "두목을 만나고 싶어? 오늘은 더 이상 면회 없어. 아침에 다시 와.";
			link.l1 = "좋아...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Narval_soldier":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("이봐, 조심해라, 저 미친놈이다! 무장해!","적이 여기 있다! 무기를 들어라!","이 자식아! 이제 제대로 맛 좀 보게 해주지!");
				link.l1 = "젠장!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! 어떻게 지내?";
				link.l1 = "괜찮아, 고마워...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "이봐, 지금은 말할 기분 아니야. 어서 가...";
				link.l1 = "좋아.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_soldier";
		break;
		
		case "negotiations":
			dialog.text = "그래, 그래... 진정해라. 처음부터 제독에게서 왔다고 했어야지. 보다시피 여기엔 온갖 사람들이 돌아다니고 있거든...";
			link.l1 = "이제야 나를 통과시켜 주는 거야? 고마워!";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			DialogExit();
			NextDiag.CurrentNode = "negotiations_2";
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду Гринспи
		break;
		
		case "negotiations_2":
			dialog.text = "가라, 너는 허락받았으니...";
			link.l1 = "오, 정말이야? 믿기지가 않네.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_2";
		break;
		
//------------------------------------- фразы гардов ривадос --------------------------------------------
		// пост ривадос на проход на Фурию и Веласко
		case "Rivados_warning":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("이봐, 조심해라, 미친놈이 날뛰고 있어! 무장해!","적이 여기 있다! 무기를 들어라!","이런, 이 썩을 놈아! 이제 제대로 맛 좀 보여주지!");
				link.l1 = "젠장!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "rvd_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "멈춰! 내 뒤에 있는 영토는 리바도스 클랜의 땅이야. 너 같은 이방인은 초대 없이는 통과할 수 없어. 암호를 알고 있나?";
					link.l1 = "그래.";
					link.l1.go = "Rivados_warning_yes";
					link.l2 = "아니.";
					link.l2.go = "Rivados_warning_no";
				}
				else // если друг ривадос
				{
					dialog.text = "아, "+GetFullName(pchar)+"! 만나서 반갑네! 여기서 자유롭게 돌아다녀도 된다고 들었어. 환영하지!";
					link.l1 = "고마워, 친구!";
					link.l1.go = "exit";
				}
				location.rvd_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "암호를 잊지 않았길 바란다...";
					link.l1 = "걱정하지 마...";
					link.l1.go = "exit";
				}
				else // если друг ривадос
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! 어떻게 지내?";
					link.l1 = "괜찮아, 고마워...";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_warning_yes":
			dialog.text = "가도 된다. 저 녀석이 너한테 암호를 요구할 거다.\n우릴 속일 생각이 조금이라도 있다면 지금 당장 떠나는 게 좋을 거야.\n경고는 했으니.";
			link.l1 = "알겠어, 친구. 이해했어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_no":
			dialog.text = "호호! 암호도 없이 우리를 찾아오다니, 너 정말 용감하거나 멍청한 거겠지. 아니면 장난치는 거냐? 좋아, 가 봐라. 나는 막으러 온 게 아니라 경고하러 온 거니까. 정말 암호를 모른다면 조심해라!";
			link.l1 = "알겠어, 친구. 이해했어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "뭐야, 뭘 원하는데? 지나가든가 꺼져!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "미안하오, "+pchar.name+", 하지만 나는 근무 중이야. 에디가 말을 많이 하지 말라고 했거든.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_parol":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("이봐, 조심해라, 미친놈이 날뛰고 있다! 무장해!","적이 여기 있다! 무기를 들어라!","아, 이 썩을 놈아! 이제 우리가 본때를 보여주지!");
				link.l1 = "젠장!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "미안하오, "+pchar.name+", 하지만 나는 근무 중이야. 에디가 말 많이 하지 말라고 했거든.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "거기서 멈춰! 너 리바도스가 아니잖아!";
			link.l1 = "지나가고 싶어.";	
			link.l1.go = "Rcheck_parol";
		break;
		
		case "Rcheck_parol":
			dialog.text = "그럼 암호를 말해. 크고 분명하게 말해야 해.";
			sTotalTemp = sRvdParol;
			if (CheckAttribute(pchar, "questTemp.LSC.RParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_" + (281 + rand(11)));
				link.l1.go = "Rcheck_parol_wrong";

				link.l2 = StringFromKey("QuestsUtilite_" + (293 + rand(11)));
				link.l2.go = "Rcheck_parol_wrong";

				link.l3 = StringFromKey("QuestsUtilite_" + (305 + rand(11)));
				link.l3.go = "Rcheck_parol_wrong";

				link.l4 = StringFromKey("QuestsUtilite_" + (317 + rand(11)));
				link.l4.go = "Rcheck_parol_wrong";
				
				switch (rand(3))
				{
					case 0:
						link.l1 = sTotalTemp;
						link.l1.go = "Rcheck_parol_1";
					break;

					case 1:
						link.l2 = sTotalTemp;
						link.l2.go = "Rcheck_parol_1";
					break;

					case 2:
						link.l3 = sTotalTemp;
						link.l3.go = "Rcheck_parol_1";
					break;

					case 3:
						link.l4 = sTotalTemp;
						link.l4.go = "Rcheck_parol_1";
					break;
				}
			}
			else
			{
				link.l1 = "무슨 암호? 비켜, 안 그러면...";
				link.l1.go = "Rcheck_parol_wrong";
			}
		break;
		
		case "Rcheck_parol_1":
			dialog.text = "맞아. 지나가.";
			link.l1 = "고마워, 친구...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			pchar.questTemp.LSC.parol_rvd = "true";
		break;
		
		case "Rcheck_parol_wrong":
			dialog.text = "하하! 손님이 왔군! 우리 어떤 놈들인지 보여주자!";
			link.l1 = "젠장!";
			link.l1.go = "Rcheck_parol_fight";
		break;
		
		case "Rcheck_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Rivados_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("이봐, 조심해라, 미친놈이 날뛰고 있어! 무장해!","적이 여기 있다! 무장하라!","아, 이 썩을 놈아! 이제 우리가 제대로 맛 좀 보여주지!");
				link.l1 = "젠장!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			dialog.text = "여기 서 있지 말고, 어서 가!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
		break;
		
		// у резиденции
		case "Rivados_residence":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("이봐, 조심해라, 미친놈이 날뛰고 있다! 무장해!","적이 여기 있다! 무기를 들어라!","아, 이 썩을 자식! 이제 제대로 맛 좀 보여주지!");
				link.l1 = "젠장!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
				{
				dialog.text = TimeGreeting()+", "+pchar.name+"! 문이 열려 있으니, 에디랑 치미셋을 보고 싶으면 들어가도 돼. 둘 다 너를 보면 기뻐할 거야.";
				link.l1 = "좋아...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else // лесник - режим пропуска 
				{	
				dialog.text = TimeGreeting()+", "+pchar.name+"! 에디와 치미셋을 보고 싶으면, 그들은 이미 쉬고 있어. 아침에 다시 오면, 너를 반가워할 거야.";
				link.l1 = "좋아...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "에디 선실 안에서는 나르발 친구들이 할 일이 없어! 이건 그의 직접적인 명령이야. 썩 꺼져!";
				link.l1 = "나도 그를 보고 싶지 않았어...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (GetCharacterIndex("Chimiset") == -1) // Чимисет убит
			{
				dialog.text = "에디 선장의 선실 안에서는 네가 할 일이 없어! 그건 그 사람의 직접적인 명령이야. 꺼져!";
				link.l1 = "나도 그를 보고 싶지 않았어...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "에디를 보고 싶어? 좋아, 가 봐. 아마 너한테 잠깐 시간 내줄 거야.";
			link.l1 = "...하게 해줘서 고마워...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else // лесник режим пропуска.
			{
            dialog.text = "에디를 보고 싶어? 오늘은 더 이상 면회 안 돼. 아침에 다시 오면 에디가 잠깐 시간 내 줄 거야.";
			link.l1 = "좋아...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Rivados_soldier":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("이봐, 조심해라, 미친놈이 날뛰고 있다! 무장하라!","적이 여기 있다! 무기를 들어라!","아, 너 정말 못된 놈이구나! 이제 우리가 본때를 보여주마!");
				link.l1 = "젠장!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! 어떻게 지내?";
				link.l1 = "괜찮아, 고마워...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "이봐, 친구, 지금 말할 기분 아니야. 지나가...";
				link.l1 = "좋아.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_soldier";
		break;
//------------------------------------- фразы гардов пиратов --------------------------------------------	
		// у склада
		case "Shark_storage":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("이봐, 조심해라, 무장한 미치광이가 있다! 무기를 들어!","적이 여기 있다! 무기를 들어라!","이 자식아! 이제 네 엉덩이를 걷어차 주마!");
				link.l1 = "젠장!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "멈춰! 여긴 출입 금지 구역이다!";
			link.l1 = "좋아, 네 말대로 하지...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_storage";
		break;
		
		// у резиденции
		case "Shark_residence":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("이봐, 조심해라, 무장한 미치광이가 있다! 무기를 들어!","적이 여기 있다! 무기를 들어라!","이 자식아! 이제 네 엉덩이를 걷어차주마!");
				link.l1 = "젠장!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "멈춰! 너 우리 편 아니잖아... 상어가 널 기다린다고 했어, 아니면 그냥 아무 생각 없이 돌아다니는 거야?";
					link.l1 = "상어? 스티브 도드슨?";
					link.l1.go = "first_talk_day";
				}
				else
				{
				dialog.text = "제독께서 너를 받아주실 거다. 어서 가.";
				link.l1 = "고마워!";
				link.l1.go = "exit";
			}
			}
			else
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "어디 그렇게 급하게 가는 거야? 지금 밤인 거 안 보여? 아니면 정말로 제독이 직접 일어나서 널 맞이해 줄 거라고 생각하는 거야? 아침에 다시 와.";
					link.l1 = "말씀대로 하죠. 그런데 어디서 쉴 수 있소?";
					link.l1.go = "first_talk_night";
				}
			else
			{
				dialog.text = "늦었습니다, 지금은 제독께서 면회를 받지 않으십니다. 내일 다시 오십시오.";
				link.l1 = "좋아...";
				link.l1.go = "exit";
			}
			}
			NextDiag.TempNode = "Shark_residence";
		break;
		
		case "Shark_soldier":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("이봐, 조심해라, 무장한 미치광이가 있다! 무기를 들어라!","적이 여기 있다! 무장하라!","이 자식아! 이제 네 엉덩이를 걷어차 주마!");
				link.l1 = "젠장!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "제독이 내가 말하는 걸 보면 기분 안 좋아할 거야. 얼른 가.";
			link.l1 = "좋아...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_soldier";
		break;
		
		case "first_talk_night":
			dialog.text = NPCStringReactionRepeat("술 취했어? 돌아가서 다리를 건너 두 척의 배를 지나가면 또 다른 다리가 나올 거야. 그 다리를 건너면 선술집이 있어. 거기서 자.","나 열받게 하려고 그러는 거냐? 방금 뭐 하라고 말했잖아. 꺼져!","가서 좀 자라, 술에 쩔은 얼굴아...","꺼져!!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("감사합니다, 나리. 사실 좀 더 예의 있게 말할 수도 있겠네요...","미안해, 내가 깜빡했어...","나 안 취했어!","뭐?!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "first_talk_day":
			dialog.text = "그렇게 놀란 얼굴 하지 마라, 이봐. 스티브 샤크가 우리 제독인 건 다 아는 사실이야. 그와 볼 일이 있나?";
			link.l1 = "그래, 젠장! 그 자와 볼 일이 있는데, 급한 일이야.";
			link.l1.go = "first_talk_day_1";
		break;
		
		case "first_talk_day_1":
			dialog.text = "그래서 무슨 일인데?";
			link.l1 = "이 일은 상어한테만 따로 말할 거야. 나는 얀 스벤손을 위해 일하고 있는데, 그 사람 알아?";
			link.l1.go = "first_talk_day_2";
		break;
		
		case "first_talk_day_2":
			dialog.text = "숲의 악마? 하! 메인 절반은 그 자를 다 안다. 이봐, 꼬마야, 고집 부리지 마라. 네가 뭔지 설명하든가, 아니면 내가 화내기 전에 꺼져라. 상어가 쓸모없는 놈들은 봐주지 말라고 했고, 난 그냥 명령대로 하는 거다.";
			link.l1 = "좋아. 자, 이 편지를 봐. 숲의 악마가 상어에게 쓴 거야.";
			link.l1.go = "first_talk_day_3";
		break;
		
		case "first_talk_day_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(흘끗)... 좋아. 스티브가 흥미로워할 거라 생각해. 지나가.";
			link.l1 = "정말이야? 번거롭지 않다면 편지 돌려줘, 부탁이야.";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "first_talk_day_5";
			else link.l1.go = "first_talk_day_4";
		break;
		
		case "first_talk_day_4":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			LocatorReloadEnterDisable("LostShipsCity_town", "reload2", true); //закрываем кладовку со стороны моря
			pchar.quest.LSC_entry_pantry.over = "yes"; //снять прерывание на арест
			pchar.quest.LSC_findMary.over = "yes"; //снять прерывание на Мэри
			pchar.questTemp.LSC = "entrance"; //меняем флаг
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
			// закрываем вход к Мэри
			LocatorReloadEnterDisable("LostShipsCity_town", "reload60", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload61", true);
		break;
		
		case "first_talk_day_5":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
		break;
		
		case "shark_guard_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_SHARK");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
