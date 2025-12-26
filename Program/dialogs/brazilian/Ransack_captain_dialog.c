// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;
    
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
		//--> Jason, Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace.Prisoner") && GetFullName(npchar) == pchar.questTemp.FalseTrace.CapName)
		{
			dialog.text = "O que você quer, capitão? Veio negociar meu resgate? Quero que saiba que me importo com o destino da garota...";
			link.l1 = "Está falando da Katerine Rayner? Já estou sabendo disso, "+pchar.questTemp.FalseTrace.CapName+". Ela me pediu para falar com você.";
			link.l1.go = "FalseTrace_Prisoner";
			break;	
		}
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "Veja bem, dom Juan, traição é uma coisa abominável...";
			link.l1.go = "FMQG";
			break;	
		}
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear()+"Eu sou seu prisioneiro, "+GetAddress_Form(NPChar)+". Mas eu quero que você saiba que "+NationNameNominative(sti(NPChar.nation))+" nunca paga pelo seu povo. Estamos todos por nossa conta.";
				link.l1 = "Bem... Vejo que não vou lucrar nada com você. Pelo menos posso entregar você como criminoso em qualquer colônia.";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "Olha, você é um lutador habilidoso e eu preciso de gente como você. Gostaria de servir sob meu comando?";
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear()+"Eu sou seu prisioneiro, "+GetAddress_Form(NPChar)+". "+NationNameNominative(sti(NPChar.nation))+" vou pagar um bom preço pela minha liberdade.";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "Olha, você é um marinheiro habilidoso e eu preciso de gente como você. Gostaria de servir sob meu comando?";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = "Não estamos longe de "+GetCityName(attrLoc)+". E eu poderia te deixar ir aqui.";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "Vá até o contramestre, peça para ele te arrumar um beliche. Você pode desembarcar no próximo porto.";
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = "Acho que você vai ser um ótimo escravo – forte e obediente.";
			link.l4.go = "Slave_1";
			link.l5 = "Você ignorou uma ordem para baixar as velas e resistiu à força. Vai ser enforcado por isso. O contramestre já recebeu minhas ordens.";
			link.l5.go = "PunishmentAction";
			link.l99 = "Eu sei.";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "tip-off"
						dialog.text = RandPhraseSimple("Capitão, gostaria de ouvir minha proposta para uma alternativa mais lucrativa ao meu resgate?","Eu entendo que aqui não há espaço para barganha, mas gostaria de ouvir minha proposta?");
						link.l1 = "Estou ouvindo.";	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = "Capitão, por que você simplesmente não me solta? Eu não tenho valor nenhum pra você. Se me vender para os escravistas, vai ganhar só algumas moedas e uma reputação ruim.";
						link.l1 = "E se eu simplesmente te soltar, não vou ganhar nada...";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = "Você ignorou uma ordem para baixar as velas e resistiu com violência. Vai ser enforcado por isso. O contramestre já recebeu minhas ordens.";
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = "Você é mesmo insistente, então acho que posso te dar o que quer. Agora você é um homem livre. Saia do meu navio.";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("Não teste a minha paciência. Você já teve sorte de sair vivo.","Eu tenho meus próprios planos para você.","Suponho que você ainda possa ser útil para mim no futuro.");
						link.l3.go = "exit";	
					break;
					
					case 2: // "ransom"
						dialog.text = "Capitão, essa incerteza está me matando. Posso saber o que pretende fazer comigo?";
						link.l1 = "Você tem algo para me oferecer?";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple("Ainda não tenho nenhuma opinião sobre você.",RandPhraseSimple("Planos? Uma bala de canhão no seu pescoço? Tô brincando, ha!","Você é meu prisioneiro e tenho todo o direito de fazer com você o que eu quiser. Sua opinião não tem valor aqui."));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "Capitão, por que você simplesmente não me deixa ir? Você não precisa de mim. Virar pirata foi minha única opção, já que não tenho habilidades valiosas nem educação. Tudo o que eu queria era ganhar algum dinheiro e depois me aposentar.";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "Olha, você é um lutador habilidoso e eu preciso de gente perigosa como você. Gostaria de ser meu oficial?";
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase("Sem piedade para você. Já há bandidos demais no mar. Pelo menos agora vai ter um a menos navegando."," Algum problema, 'lobo do mar'? Fique aqui e fique quieto.","Forca espera por todos da sua laia. Vou te entregar às autoridades, e isso será uma grande lição para qualquer pirata.");	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "Capitão, eu imploro... Me liberte. Tenho família e filhos, e eles não vão sobreviver sem mim.";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "Olha, você é um marinheiro habilidoso e eu preciso de gente como você. Gostaria de servir sob meu comando?";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("Eu tenho meus próprios planos para você.","Suponho que você ainda possa ser útil para mim no futuro.","Você é meu prisioneiro e eu tenho todo o direito de fazer com você o que eu quiser.");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("Capitão, eu perdi a luta e imploro pela sua misericórdia. ","Capitão, peço pela sua generosidade. Entendo que não há motivo para me tratar como um prisioneiro de guerra, então peço que me poupe. Dou minha palavra de que evitarei encontrá-lo no mar.");
						link.l2 = LinkRandPhrase("Não teste a minha paciência. Você já teve sorte de sair vivo.",RandPhraseSimple("Eu tenho meus próprios planos para você.","Suponho que você ainda possa me ser útil no futuro."),RandPhraseSimple("Você é meu prisioneiro e tenho todo o direito de fazer com você o que eu quiser. Sua opinião não tem valor aqui.","Você é... bem, você era capitão de um navio de guerra e sabia dos riscos. Não tente se fazer de santo aqui."));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "Olha, você é um lutador habilidoso e eu preciso de gente dura como você. Gostaria de ser meu oficial?";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = "Não estamos longe de "+GetCityName(attrLoc)+". E eu poderia te deixar ir aqui.";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "Vá até o contramestre, peça para ele te arrumar um beliche. Você pode desembarcar no próximo porto.";
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = "Maldito seja! Vá falar com o contramestre, peça pra ele te arrumar um armário. Você pode desembarcar no próximo porto. E lembre-se, nosso próximo encontro será o último.";
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = "Você ignorou a ordem de baixar as velas e resistiu à força. Vai ser enforcado por isso. O contramestre já recebeu minhas ordens.";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = "Criminoso? Você só pode estar brincando comigo,"+GetAddress_Form(NPChar)+"!";
			link.l1 = "Sem brincadeira. Você é um pirata.";
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "Servir sob seu comando? Prefiro alimentar os tubarões!";
				link.l1 = "Cuide da sua língua ou vai acabar servindo de comida para eles.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ser seu oficial, "+GetAddress_Form(NPChar)+"? Concordo. Eu sei o que faço e não tenho nada a perder.";
				link.l1 = "Fechado! Vai lá e faz o teu trabalho.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Espere um momento, mudei de ideia.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("É uma oferta tentadora... mas tenho que recusar. Por princípio.","Desculpe, mas depois do que você fez com meus amigos... É impossível.","Não, capitão. Depois de todo esse terror, não consigo mais fazer esse trabalho. Fiz uma promessa: se a Virgem Santíssima ouvir minhas preces e me conceder a liberdade, não vou mais navegar.");
				link.l1 = "A escolha é sua. Não vou insistir.";	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Por que não? Sou um capitão sem sorte, perdi meu navio e não me resta nada em terra. Só contas e dívidas...";
				link.l1 = "Fechado! Vá até o contramestre e pegue seus suprimentos. Depois eu vou te dar um posto no meu navio.";	
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Espere um pouco, mudei de ideia.";
				link.l2.go = "exit";
			}
		break;
		
		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // освободили пленника
            DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";
            
			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;
				
		case "Slave_1":
			dialog.text = "Mas "+GetAddress_Form(NPChar)+", você não pode fazer isso! Eu já me rendi.";
            link.l1 = "Cale a boca! ... Amarrem ele.";
			link.l1.go = "Slave_2";
			link.l99 = "Certo. Fique aqui até eu decidir...";
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
            if (rand(5) == 1)
            {
    			dialog.text = "De jeito nenhum! Prefiro morrer a virar escravo!";
                link.l1 = "Pare com isso! Isto é uma ordem!... Contramestre! Limpe a carga...";
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "Açougueiro! Pessoal, venham comigo, não temos nada a perder!";
                        link.l1 = "Escolha errada, senhoras. Eu mesmo lido com motins, e faço isso bem rápido...";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "De jeito nenhum! Prefiro morrer lutando!";
						link.l1 = "Como quiser...";
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
					dialog.text = "Ah, eu concordo. Não tenho escolha.";
                    link.l1 = "Excelente. É melhor ser um escravo vivo do que um herói morto.";
        			link.l1.go = "Slave_3";				
    			}			
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  пленника в рабы
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", você é mesmo tão generoso, me libertando sem pedir resgate?";
            link.l1 = "Sim, sou eu. Agora você está livre,"+GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "Hm... Você tem razão! Preciso de mais tempo para decidir.";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "Obrigado, "+GetFullName(PChar)+"! Vou rezar por você.";
            link.l1 = "Vá agora, e tente continuar vivo, senão minha generosidade terá sido em vão.";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;
		
		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", 2);
        	DialogExit();
        break;	

		case "free_withoutFee_4":	
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("Obrigado, capitão. Nunca vou esquecer a sua bondade. Vou deixar este trabalho e consertar pequenos barcos em portos tranquilos. Eu consigo fazer isso.","Obrigado, capitão! Juro que vou largar essa vida ingrata e virar pescador.");
					link.l1 = "Se estiver falando a verdade, desejo-lhe sorte; se não, reze para nunca mais me encontrar...";	
				break;
				case "trade":
					dialog.text = "Nem sei como te agradecer, capitão. Já tinha perdido as esperanças. Vou contar pra todo mundo sobre a sua bondade. Dou minha palavra, vou acender uma vela por você! Só preciso chegar numa igreja.";
					link.l1 = "Adeus. E da próxima vez, nem pense em resistir. Se atirar em mim, será sentença de morte para você e sua tripulação.";
				break;
				case "war":
					dialog.text = "Meu agradecimento, capitão. Vou rezar por você.";
					link.l1 = "Boa sorte, e lembre-se: se decidir me caçar, será o seu fim.";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;
		
		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // освободили пленника        	
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;		

		case "free_in_sea_battle_all":
			//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                        	ReleasePrisoner(offref); // освободили пленника
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;
		
		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "Mas "+GetAddress_Form(NPChar)+", você não pode fazer isso! Eu já me rendi.";
			link.l1 = "Só depois que seus homens se foram. Você os traiu... Contramestre! Levem-no.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Bem... Preciso de um tempo para pensar. Fique aqui.";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "Açougueiro! Gente, não temos nada a perder!";
                    link.l1 = "Escolha errada, senhoras. Eu mesmo lido com motins, e faço isso bem rápido...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "De jeito nenhum! Prefiro morrer lutando!";
					link.l1 = "Como quiser...";
					link.l1.go = "free_in_sea_battle_1";
				}	
    		}
			else
    		{
				dialog.text = "Pelo menos me dê um tempo para rezar...";
                link.l1 = "Reze, se quiser.";
        		link.l1.go = "PunishmentAction2";				
    		}						
		break;
		
		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";		
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;
		
		case "free_tip_off":
			dialog.text = "Tenho algumas informações interessantes que podem ser úteis para um homem como você. Mas preciso da sua garantia de que vou ganhar minha liberdade em troca.";
			link.l1 = "Como posso te dar alguma garantia se nem conheço a sua proposta? Duvido que sua informação vá me servir para alguma coisa.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Posso apenas lhe dar minha palavra.";
			link.l2.go = "free_tip_off_1";
		break;
		
		case "free_tip_off_0":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;
		
		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "He proposed me a freight but this guy was too greedy and I rejected the offer.";  
				break;
				case "war":
					sTmp = "I have escorted him a few times as a commander of a convoy.";
				break;
				case "pirate":
					sTmp = "I had an idea to rob him once but I have never had a single chance to do that.";
				break;
			}
			dialog.text = "Certo. Isso já basta pra mim. Agora, direto ao assunto, em "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" é a casa de um comerciante rico "+NPChar.Hold_GenQuest.Name+". "+"Ele fez sua fortuna no navio dele '"+NPChar.Hold_GenQuest.ShipName+" vendendo "+GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name+"Acc"))+" com rota : "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.FromCity)+" - "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.ToCity)+". "+"Quando ele está com muita carga, paga por escolta."+sTmp+" Tenho certeza de que esta informação vale mais para você do que a vida de um só homem.";
			link.l1 = "Duvido que essa informação vá me ser útil. Não vou caçar comerciantes pacíficos.";	
			link.l1.go = "free_tip_off_0";
			link.l2 = "Não sei se essa informação vai me servir de alguma coisa, mas dei minha palavra. O contramestre vai te colocar com minha tripulação e te soltar no porto mais próximo.";
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = "Meu agradecimento, capitão! Eu nunca duvidei da sua honestidade!";
			link.l1 = RandPhraseSimple(RandPhraseSimple("Gostaria de poder dizer o mesmo sobre você","Desculpe, mas não posso dizer o mesmo de você."),RandPhraseSimple("Vá, e lembre-se que da próxima vez não serei tão generoso.","Vá e fique fora do meu caminho. Da próxima vez não vou acreditar tão fácil em você."));
			link.l1.go = "free_tip_off_3";
		break;
		
		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;			
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation; 
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity; 
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;				
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City); 
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc"))); 
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
			
			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();			
		break;
	
		case "free_buyout":
			dialog.text = "E eu tenho uma proposta para você. Em "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" vive, meu amigo, "+NPChar.Hold_GenQuest.Name+" é o nome dele. Já tivemos um negócio juntos."+"Encontre-o lá. Tenho certeza de que ele vai te pagar uma boa quantia. Ele me deve, e eu mesmo vou acertar as contas com ele.";
			link.l1 = "Seu amigo, é? Vamos ver quem é.";	
			link.l1.go = "free_buyout1";
			link.l2 = "Por que eu deveria procurar seu amigo se posso conseguir um resgate logo no primeiro porto?";
			link.l2.go = "free_tip_off_0";
		break;
	
		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);
			
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "Na verdade, conheço um homem que tem um belo tesouro, mas não tem coragem de usá-lo.";
			link.l1 = "O que você quer dizer?";
			link.l1.go = "free_by_hoard1";
			link.l2 = "Poupe-me das suas histórias. É melhor se preocupar com a sua alma.";
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = "Estou te contando uma história que leva a um grande tesouro. Em troca, preciso da sua palavra de que vai me deixar ir no próximo porto.";
			link.l1 = "Eu mesmo vou decidir quando e o que fazer com você. Suas 'histórias' não vão mudar nada.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Estou ouvindo. Dou minha palavra.";
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = "Confio em alguém tão honrado "+GetSexPhrase("homem","mulher")+". Pessoas como você sempre cumprem a palavra! Não importa se o mundo inteiro está pegando fogo, você vai manter sua promessa! Estou certo, capitão?";
			link.l1 = "Conte sua história, ou eu te deixo ir agora mesmo... por cima da borda e sem cabeça.";
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = "Ha-ha, bela piada... Agora escute. Tem um sujeito em "+XI_ConvertString("Colony"+NPChar.Hold_GenQuest.City+"Voc")+" named "+NPChar.Hold_GenQuest.Name+", ele era um sujeito bem imprudente na juventude. Naquela época, fazia muitos 'negócios'..."+"Então, uma vez na taverna, ele me contou que era membro de "+GetName(NAMETYPE_VIP,NPChar.Hold_GenQuest.PirateName,NAME_ACC)+"   bando e ele viu como aqueles piratas estavam enterrando um tesouro."+" Ele mandou matar cinco dos próprios companheiros por causa desse tesouro... Diziam que ele tinha sido pego e enforcado, mas a verdade é que ele largou o negócio e resolveu formar uma família. Ele lembrava onde estava o tesouro, chegou até a desenhar um mapa. Me convidou para ir junto procurar o tesouro. Muito supersticioso, achava que o tesouro estava manchado de sangue, então tinha medo de ir sozinho. Confesso que, pelo mesmo motivo, também não tive coragem de ir. "+"Ele estava pronto para vender o mapa, mas por que eu precisaria dele se eu nunca iria até lá mesmo...\nEssa é a minha história... Acho que um homem corajoso como você vai achar útil, e o mapa é bem barato, aliás.";
			link.l1 = "E você realmente espera que eu acredite nisso? Sua história não é verdadeira, então estou encerrando nosso acordo.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "História interessante, embora eu não acredite muito nela. Mas dou minha palavra, vá e diga ao contramestre para te arrumar um beliche. Você está livre.";
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = "Meu agradecimento, capitão! Agora vejo o valor da palavra de um homem "+GetSexPhrase("cavalheiro!","senhora!");
			link.l1 = "Vá e fique fora do meu caminho. Da próxima vez não vou te deixar escapar tão fácil.");
			link.l1.go = "free_by_hoard6";
		break;
		
		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();					
		break;
		
		case "free_in_sea":
			dialog.text = "Mas, "+GetAddress_Form(NPChar)+", estamos em alto-mar! É como se você tivesse me executado!";
			link.l1 = "Era isso que você queria. Adeus. O contramestre vai cumprir minha ordem.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Certo, ainda não decidi.";
			link.l2.go = "exit";
		break;		
		
		//--> Jason, Ложный след
		case "FalseTrace_Prisoner":
			dialog.text = "Katerine! Ela realmente pediu pra você vir aqui? Que moça maravilhosa...";
			link.l1 = "Vamos deixar a poesia de lado, capitão, e falar de assuntos mais sérios. Vou lhe contar sobre a situação atual, e espero uma resposta sua. Sua resposta vai determinar tanto o seu destino quanto o de Katerine.";
			link.l1.go = "FalseTrace_Prisoner_1";
		break;
		
		case "FalseTrace_Prisoner_1":
			dialog.text = "Estou ouvindo, capitão.";
			link.l1 = "Eu abordei seu fluyt porque Adam Rayner, o marido da Katerin, me disse que havia muita prata no seu navio. Esse truque permitiu que ele recuperasse uma mulher que já foi dele, e que fugiu dele para ficar com você.";
			link.l1.go = "FalseTrace_Prisoner_2";
		break;
		
		case "FalseTrace_Prisoner_2":
			dialog.text = "Adam? Aquele desgraçado? Foi tudo plano dele! Agora entendo... Sim, ajudei a Katrine a fugir três meses atrás. Pobrezinha, você não faz ideia de como ele tratava ela...";
			link.l1 = "Ela era esposa dele e eu não dou a mínima para o que aconteceu, isso não é problema meu. Eu errei ao subir no seu fluyt, mas agora é tarde para falar disso. Adam prometeu me pagar pela minha ajuda.";
			link.l1.go = "FalseTrace_Prisoner_3";
		break;
		
		case "FalseTrace_Prisoner_3":
			dialog.text = "Adam fez uma promessa? Ha-ha! E você acreditou nele? Capitão, você ao menos sabe que tipo de pessoa ele é? Ele...";
			link.l1 = "A Katerine já me contou muito sobre ele e se esforçou bastante pra isso. Mas a proposta dele faz sentido, e embora eu não tenha motivo pra confiar nesse desgraçado, talvez dessa vez ele esteja falando a verdade. Então vamos direto ao ponto...";
			link.l1.go = "FalseTrace_Prisoner_4";
		break;
		
		case "FalseTrace_Prisoner_4":
			dialog.text = "";
			link.l1 = "Eu ia pedir resgate por você às autoridades e entregar Adam e Katerine para "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Acc")+", then get from Adam the information about Squint-Eyed Solly's gold and sail to it. But Katerine persuaded me to speak with you first; she said you might offer me something better and more reliable than Adam did, in exchange for your lives and freedom.";
			link.l1.go = "FalseTrace_Prisoner_5";
		break;
		
		case "FalseTrace_Prisoner_5":
			dialog.text = "";
			link.l1 = "É por isso que estou aqui conversando com você. Já terminei. Agora é a sua vez. Pense no que eu disse e no que a Katerine disse, e me diga o que acha. Você não tem muito tempo.";
			link.l1.go = "FalseTrace_Prisoner_6";
		break;
		
		case "FalseTrace_Prisoner_6":
			dialog.text = "Capitão! Embora eu não ache que você seja um homem bom, você ouviu os pedidos de uma pobre moça e veio até aqui. Isso me mostra que você pode ser honrado e sentir compaixão. Não preciso de tempo, estou pronta para te fazer minha proposta.";
			link.l1 = "Sério? Excelente! Então, estou ouvindo.";
			link.l1.go = "FalseTrace_Prisoner_7";
		break;
		
		case "FalseTrace_Prisoner_7":
			dialog.text = "Você vai prender Adam Rayner e acorrentá-lo. Depois, vai levar a mim e à Katherine para "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Não desembarque na cidade, afinal, foi você quem afundou meu fluyt, deixe nós três em "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+"\nI would also ask you for a weapon. We will go to the city through the jungle, and I'll make sure that the scum pays not only for his crimes but for yours as well. He deserves it\nYou have my word that your name won't come up. In return, I will give you true information concerning a ship carrying the gold of an enemy state\nIt won't be a great challenge for you, but it does have teeth; you will gain a fine booty. Much better than my ransom and the so-called Squint-Eyed Solly's treasures. Do we have a deal?";
			link.l1 = "Não gosto do seu plano. Acho que as autoridades locais vão organizar uma caçada atrás de mim assim que eu deixar as margens de "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+". Não, capitão, não vou arriscar meu pescoço. Nossa conversa acabou.";
			link.l1.go = "FalseTrace_Prisoner_8";
			link.l2 = "Bem, parece que a Katerine estava certa. Gostei da sua proposta. Adam Rayner será preso. Vou providenciar isso agora mesmo. Você será liberado assim que prendermos o Adam. Até logo, capitão!";
			link.l2.go = "FalseTrace_Prisoner_9";
		break;
		
		case "FalseTrace_Prisoner_8":
			DialogExit();
			AddQuestRecord("FalseTrace", "9");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			bQuestDisableMapEnter = false;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_Prisoner_9":
			DialogExit();
			AddQuestRecord("FalseTrace", "10");
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			AddDialogExitQuestFunction("SetCheckForGoldShip");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FalseTrace.PrisonerID = npchar.id;
			Pchar.questTemp.FalseTrace.PrisonerIDX = GetCharacterIndex(npchar.id);
		break;
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Veio aqui para pregar ou para fazer negócios?";
			link.l1 = "Para fazer negócios. Preciso do seu parceiro de crime - Bertrand Pinette. Estou encrencado por causa dele. Onde posso encontrá-lo, hein?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Por que você acha que eu te contaria isso?";
			link.l1 = "É o seu pescoço em jogo. Vou te levar para Basse-Terre, entregar você ao governador e receber a recompensa por capturar um desertor que ajudou Carlos de Milyar a escapar. A escolha é sua. Ou você me diz onde está Pinette, ou nós dois vamos para Guadalupe.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "Então você sabe de tudo... Está bem, vou contar tudo o que sei sobre Bertrand Pinette, mas em troca você precisa me deixar livre.";
			link.l1 = "Vai, fala então. Vou te deixar na Baía dos Mosquitos, igual da última vez. Mas se mentir pra mim, eu volto e boto fogo naquela plantação que o Don Carlos te deu. E ainda aviso Basse-Terre onde você está, assim não serei o único atrás de você.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "Primeiro, me deixe lá. Assim vou me sentir mais seguro, e juro que vou te contar tudo.";
			link.l1 = "Tudo bem. Não é como se você fosse a algum lugar.";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "16");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FMQG.PrisonerID = npchar.id;
			Pchar.questTemp.FMQG.PrisonerIDX = GetCharacterIndex(npchar.id);
			pchar.quest.FMQG_SailMoskitos.win_condition.l1 = "location";
			pchar.quest.FMQG_SailMoskitos.win_condition.l1.location = "Shore47";
			pchar.quest.FMQG_SailMoskitos.function = "FMQG_ArriveMoskitos";
			pchar.questTemp.FMQG = "to_moskitos";
			AddMapQuestMarkShore("Shore47", true);
			bDisableMapEnter = false; // Rebbebion, теперь можно
		break;
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
	}
}
