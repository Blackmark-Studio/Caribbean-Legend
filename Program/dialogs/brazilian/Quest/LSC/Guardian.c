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
			dialog.text = "O que diabos você quer?";
			link.l1 = "Não, não é nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- фразы гардов нарвалов --------------------------------------------
		// пост нарвалов на проход на Сан-Габриэль
		case "Narval_warning":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Rapazes, cuidado, tem um louco! Às armas!","O inimigo está aqui! Às armas!","Ah, seu desgraçado! Agora vamos te dar uma lição!");
				link.l1 = "Porra!";
				link.l1.go = "check_parol_fight";
				break;
			}
			ref location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Pare aí, camarada. Território dos Narvais à frente, entrada proibida para estranhos. Só passa com convite. Sabe a senha?";
					link.l1 = "Sim.";
					link.l1.go = "Narval_warning_yes";
					link.l2 = "Não.";
					link.l2.go = "Narval_warning_no";
				}
				else // если друг нарвалам
				{
					dialog.text = "A-ah, "+GetFullName(pchar)+"! Olá, amigo, nos disseram que você pode andar livremente por aqui. Seja bem-vindo!";
					link.l1 = "Obrigado, amigo!";
					link.l1.go = "exit";
				}
				location.nrv_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Espero que você não tenha esquecido a senha...";
					link.l1 = "Não se preocupe...";
					link.l1.go = "exit";
				}
				else // если друг нарвалам
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Como você está?";
					link.l1 = "Bem, obrigado!";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_warning_yes":
			dialog.text = "Então vá e diga isso para o valentão ali. Não tente enganá-lo, nossos rapazes com mosquetes sabem o que fazer. Se estiver pensando em alguma artimanha, é melhor dar meia-volta e ir embora. Agora. Eu te avisei.";
			link.l1 = "Tudo bem, amigo. Entendi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_no":
			dialog.text = "Então você não tem nada pra fazer aqui, a menos que esteja pensando em acabar com a própria vida, claro. Ou está só brincando, hein? Está de gozação comigo? Na verdade, não me importo. Pode descer, meu trabalho é avisar, não impedir. Se não souber a senha, não volta mais.";
			link.l1 = "Tá bom, camarada. Entendi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "O que mais você quer? Desça até o 'San Gabriel' ou suma daqui!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Me desculpe, "+pchar.name+", mas estou de serviço. Não me incomode, amigo. Siga em frente!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_parol":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Rapazes, cuidado, lá vem o maluco! Às armas!","O inimigo está aqui! Às armas!","Ah, seu desgraçado! Agora vamos te dar uma lição!");
				link.l1 = "Merda!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Me desculpe, "+pchar.name+", mas estou de serviço. Não me incomode, amigo. Siga seu caminho!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol";
				break;
			}
			dialog.text = "Fique exatamente onde está! Você não é um dos nossos!";
			link.l1 = "Estou de pé, de pé.";	
			link.l1.go = "check_parol";
		break;
		
		case "check_parol":
			dialog.text = "Diga a senha, bem clara e em voz alta.";
			sTotalTemp = sNrvParol;
			if (CheckAttribute(pchar, "questTemp.LSC.NParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_"+(281+rand(11)));
				link.l1.go = "check_parol_wrong";
				link.l2 = StringFromKey("QuestsUtilite_"+(293+rand(11)));
				link.l2.go = "check_parol_wrong";
				link.l3 = StringFromKey("QuestsUtilite_"+(305+rand(11)));
				link.l3.go = "check_parol_wrong";
				link.l4 = StringFromKey("QuestsUtilite_"+(317+rand(11)));
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
				link.l1 = "Que senha? Me deixa passar, ou então...";
				link.l1.go = "check_parol_wrong";
			}
		break;
		
		case "check_parol_1":
			dialog.text = "Tudo bem, pode prosseguir.";
			link.l1 = "Valeu, camarada...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			pchar.questTemp.LSC.parol_nrv = "true";
		break;
		
		case "check_parol_wrong":
			dialog.text = "Hum... Pessoal! Temos companhia!";
			link.l1 = "Merda!";
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
				dialog.text = LinkRandPhrase("Rapazes, cuidado, lá vem o maluco! Às armas!","O inimigo está aqui! Às armas!","Ah, seu desgraçado! Agora vamos te dar uma lição!");
				link.l1 = "Porra!";
				link.l1.go = "check_parol_fight";
				break;
			}
			dialog.text = "Ande logo! Não fique parado aqui!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;
		
		// у резиденции
		case "Narval_residence":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Rapazes, cuidado, lá vem o maluco! Às armas!","O inimigo está aqui! Às armas!","Ah, seu desgraçado! Agora vamos te dar uma lição!");
				link.l1 = "Porra!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // диалог от времени суток. лесник
			    {
					dialog.text = TimeGreeting()+", "+pchar.name+"! A porta está aberta, caso queira ver o chefe.";
					link.l1 = "Tudo bem...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else
				{
                    dialog.text = TimeGreeting()+", "+pchar.name+"! Se quiser ver o chefe, ele está dormindo agora. Volte de manhã.";
					link.l1 = "Tudo bem...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");	
                }					
				break;	
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Amigos dos pretos não têm vez aqui. Ordem direta do chefe!";
				if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
				{
					link.l1 = "Ele vai ter que me receber. Vocês estão com um problema sério, pessoal. Eu estou aqui por ordem oficial do almirante. Então abram essa maldita porta!";
					link.l1.go = "negotiations";
				}
				else
				{
				link.l1 = "Também não posso dizer que quero vê-lo...";
				link.l1.go = "exit";
				}
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Quer ver o chefe? Hm, então siga em frente.";
			link.l1 = "Obrigado por me permitir...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else
			{
            dialog.text = "Quer ver o chefe? Hoje não tem mais visitas. Volte de manhã.";
			link.l1 = "Certo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Narval_soldier":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Rapazes, cuidado, lá vem o maluco! Às armas!","O inimigo está aqui! Às armas!","Ah, seu desgraçado! Agora vamos te dar uma lição!");
				link.l1 = "Porra!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Como você está?";
				link.l1 = "Estou bem, obrigado...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Olha, camarada, não tô com cabeça pra conversa agora. Segue seu caminho...";
				link.l1 = "Tudo bem.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_soldier";
		break;
		
		case "negotiations":
			dialog.text = "Bem, bem... Calma. Você devia ter dito logo de cara que veio a mando do almirante. Veja, tem todo tipo de gente andando por aí...";
			link.l1 = "Vai me deixar passar finalmente? Obrigado!";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			DialogExit();
			NextDiag.CurrentNode = "negotiations_2";
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду Гринспи
		break;
		
		case "negotiations_2":
			dialog.text = "Siga em frente, você tem permissão para...";
			link.l1 = "Sério? Não acredito.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_2";
		break;
		
//------------------------------------- фразы гардов ривадос --------------------------------------------
		// пост ривадос на проход на Фурию и Веласко
		case "Rivados_warning":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Rapazes, cuidado, tem um maluco agressivo! Às armas!","O inimigo está aqui! Às armas!","Ah, seu desgraçado! Agora vamos te ensinar uma lição!");
				link.l1 = "Porra!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "rvd_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Pare! Os territórios atrás de mim pertencem ao clã Rivados, e nenhum estranho como você pode passar sem um convite. Você sabe a senha?";
					link.l1 = "Sim.";
					link.l1.go = "Rivados_warning_yes";
					link.l2 = "Não.";
					link.l2.go = "Rivados_warning_no";
				}
				else // если друг ривадос
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Que bom te ver! Disseram que você está livre para andar por aqui. Seja bem-vindo!";
					link.l1 = "Obrigado, amigo!";
					link.l1.go = "exit";
				}
				location.rvd_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Espero que você não tenha esquecido a senha...";
					link.l1 = "Não se preocupe...";
					link.l1.go = "exit";
				}
				else // если друг ривадос
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Como você está?";
					link.l1 = "Estou bem, obrigado...";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_warning_yes":
			dialog.text = "Pode ir então. Esse rapaz vai pedir uma senha pra você. É melhor ir embora agora se está pensando em nos enganar. Considere-se avisado.";
			link.l1 = "Tá bom, camarada. Entendi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_no":
			dialog.text = "Ho-ho! Ou você é muito corajoso ou muito tolo se vai nos visitar sem uma senha. Ou está só brincando? Pode passar então. Estou aqui para avisar, não para impedir. Mas cuidado se realmente não souber a senha!";
			link.l1 = "Tá bom, camarada. Entendi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Então, o que você quer? Vai andando ou desapareça!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Me desculpe, "+pchar.name+", mas estou de serviço. O Eddie não quer que eu converse demais.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_parol":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Rapazes, cuidado, tem um louco agressivo! Às armas!","O inimigo está aqui! Às armas!","Ah, você é um desgraçado! Agora vamos te dar uma lição!");
				link.l1 = "Porra!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Me desculpe, "+pchar.name+", mas estou de serviço. O Eddie não quer que eu converse demais.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "Pare aí mesmo! Você não é dos Rivados!";
			link.l1 = "Quero passar.";	
			link.l1.go = "Rcheck_parol";
		break;
		
		case "Rcheck_parol":
			dialog.text = "Então diga uma senha, bem alto e claro.";
			sTotalTemp = sRvdParol;
			if (CheckAttribute(pchar, "questTemp.LSC.RParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_"+(281+rand(11)));
				link.l1.go = "Rcheck_parol_wrong";

				link.l2 = StringFromKey("QuestsUtilite_"+(293+rand(11)));
				link.l2.go = "Rcheck_parol_wrong";

				link.l3 = StringFromKey("QuestsUtilite_"+(305+rand(11)));
				link.l3.go = "Rcheck_parol_wrong";

				link.l4 = StringFromKey("QuestsUtilite_"+(317+rand(11)));
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
				link.l1 = "Que senha? Me deixa passar, ou então...";
				link.l1.go = "Rcheck_parol_wrong";
			}
		break;
		
		case "Rcheck_parol_1":
			dialog.text = "Certo. Pode seguir.";
			link.l1 = "Valeu, camarada...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			pchar.questTemp.LSC.parol_rvd = "true";
		break;
		
		case "Rcheck_parol_wrong":
			dialog.text = "Ha-ha! Temos visita! Vamos mostrar quem somos!";
			link.l1 = "Merda!";
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
				dialog.text = LinkRandPhrase("Rapazes, cuidado, tem um maluco agressivo! Às armas!","O inimigo está aqui! Às armas!","Ah, você é um desgraçado! Agora vamos te dar uma lição!");
				link.l1 = "Porra!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			dialog.text = "Não fique parado aqui, siga em frente!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
		break;
		
		// у резиденции
		case "Rivados_residence":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Rapazes, cuidado, tem um maluco agressivo! Às armas!","O inimigo está aqui! Às armas!","Ah, seu desgraçado! Agora você vai aprender!");
				link.l1 = "Porra!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
				{
				dialog.text = TimeGreeting()+", "+pchar.name+"! A porta está aberta, caso queira ver o Eddie e a Chimiset. Eles vão ficar felizes em te ver.";
				link.l1 = "Tudo bem...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else // лесник - режим пропуска 
				{	
				dialog.text = TimeGreeting()+", "+pchar.name+"! Se quiser ver o Eddie e a Chimiset, eles já estão descansando. Volte de manhã, eles vão ficar felizes em te ver.";
				link.l1 = "Tudo bem...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Não há nada para os amigos dos Narvais fazerem dentro da cabine do Eddie! Esta é uma ordem direta dele. Cai fora!";
				link.l1 = "Eu também não queria vê-lo...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (GetCharacterIndex("Chimiset") == -1) // Чимисет убит
			{
				dialog.text = "Não há nada para você fazer dentro da cabine do Eddie! Isso é uma ordem direta dele. Cai fora!";
				link.l1 = "Eu também não queria vê-lo...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Quer ver o Eddie? Tudo bem, siga em frente, acho que ele pode te dar um minuto.";
			link.l1 = "Obrigado por me permitir...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else // лесник режим пропуска.
			{
            dialog.text = "Quer ver o Eddie? Hoje não tem mais visitas, volte de manhã e ele vai arrumar um tempinho pra você.";
			link.l1 = "Certo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Rivados_soldier":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Rapazes, cuidado, tem um louco agressivo! Às armas!","O inimigo está aqui! Às armas!","Ah, você é um desgraçado! Agora vamos te ensinar uma lição!");
				link.l1 = "Porra!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Como você está?";
				link.l1 = "Estou bem, obrigado...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Olha, camarada, não tô com cabeça pra conversa. Vai andando...";
				link.l1 = "Tudo bem.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_soldier";
		break;
//------------------------------------- фразы гардов пиратов --------------------------------------------	
		// у склада
		case "Shark_storage":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Rapazes, cuidado, tem um louco armado! Às armas!","O inimigo está aqui! Às armas!","Ah, seu desgraçado! Agora vamos acabar com você!");
				link.l1 = "Droga!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Pare! Esta é uma área restrita!";
			link.l1 = "Está bem, como quiser...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_storage";
		break;
		
		// у резиденции
		case "Shark_residence":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Rapazes, cuidado, tem um louco armado! Às armas!","O inimigo está aqui! Às armas!","Ah, seu desgraçado! Agora vamos acabar com você!");
				link.l1 = "Maldição!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Pare! Você não é dos nossos... O Tubarão está te esperando, ou você só está vagando por aí sem rumo?";
					link.l1 = "Tubarão? Steve Dodson?";
					link.l1.go = "first_talk_day";
				}
				else
				{
				dialog.text = "O Almirante vai te aceitar. Pode seguir.";
				link.l1 = "Obrigado!";
				link.l1.go = "exit";
			}
			}
			else
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Onde você está indo com tanta pressa? Já é noite, não está vendo? Ou acha mesmo que o almirante vai acordar só pra te receber? Volte de manhã.";
					link.l1 = "Como preferir. E onde posso descansar?";
					link.l1.go = "first_talk_night";
				}
			else
			{
				dialog.text = "Está tarde, o almirante não está recebendo agora. Volte amanhã.";
				link.l1 = "Tudo bem...";
				link.l1.go = "exit";
			}
			}
			NextDiag.TempNode = "Shark_residence";
		break;
		
		case "Shark_soldier":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Rapazes, cuidado, tem um louco armado! Às armas!","O inimigo está aqui! Às armas!","Ah, seu desgraçado! Agora vamos acabar com você!");
				link.l1 = "Droga!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "O Almirante não vai gostar se me vir conversando. Siga em frente.";
			link.l1 = "Tudo bem...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_soldier";
		break;
		
		case "first_talk_night":
			dialog.text = NPCStringReactionRepeat("Você está bêbado? Volte e atravesse a ponte, passe por dois navios, e então encontrará outra ponte que vai te levar até a taverna. Durma lá.","Você tá querendo me irritar? Acabei de te dizer o que fazer. Cai fora!","Vai dormir um pouco, cara de bêbado...","Vai embora!!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Obrigado, senhor. Na verdade, você poderia ser um pouco mais educado...","Desculpe, eu esqueci...","Eu não estou bêbado!","O quê?!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "first_talk_day":
			dialog.text = "Não fique tão surpreso, rapaz. Todo mundo sabe que Steve Shark é o nosso almirante. Você tem algum assunto com ele?";
			link.l1 = "Sim, droga! Tenho assuntos com ele e é urgente.";
			link.l1.go = "first_talk_day_1";
		break;
		
		case "first_talk_day_1":
			dialog.text = "E que tipo de negócio?";
			link.l1 = "Eu só vou contar isso para o Tubarão em particular. Estou trabalhando para Jan Svenson, você conhece ele?";
			link.l1.go = "first_talk_day_2";
		break;
		
		case "first_talk_day_2":
			dialog.text = "Diabo da Floresta? Ha! Metade da Ilha conhece esse homem. Escuta, rapaz, não seja teimoso. Ou se explica ou cai fora antes que eu perca a paciência. O Tubarão mandou não perder tempo com gente inútil e só estou fazendo o que ele mandou.";
			link.l1 = "Certo. Aqui, dê uma olhada nesta carta, foi escrita pelo Diabo da Floresta para o Tubarão.";
			link.l1.go = "first_talk_day_3";
		break;
		
		case "first_talk_day_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(olhando)... Tudo bem. Imagino que o Steve vai achar interessante. Pode ir.";
			link.l1 = "Ah, é mesmo? Se não for pedir demais, devolva a carta, por favor.";
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
