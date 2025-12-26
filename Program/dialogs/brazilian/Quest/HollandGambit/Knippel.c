// Чарли Книппель - старый артиллерист
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		//ветка на взятие 2 варианта прохождения - за Англию
		if(CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "Ah, corrente de canhão no meu traseiro! O que te traz aqui?";
			link.l1 = "Atire corrente no seu... o quê? Ah, deixa pra lá, só queria dar um oi.";
			link.l1.go = "exit";
			link.l2 = "Saudações, Sr. Knippel. Ha, agora entendo por que te chamam de Knippel. Enfim, ouvi dizer que você já serviu na Marinha Inglesa. Tenho um belo navio e uma tripulação experiente. Gostaria de oferecer meus serviços e meu navio à Coroa Inglesa... digo, à Comunidade. Você pode me dar algum conselho, me recomendar a alguém, ou talvez me ajudar com isso?";
			link.l2.go = "Knippel_check";
			break;
		}
		//за Голландию
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "Ah, corrente de canhão no meu traseiro! O que te traz aqui?";
				link.l1 = "Saudações, Sr. Knippel. Ha, agora entendo por que te chamam de Knippel. Ouvi dizer que você serviu na Marinha Inglesa, e é por isso que quero pedir sua ajuda...";
				link.l1.go = "Dominica";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Tiro de corrente o caramba! O que você quer, camarada?";
			link.l1 = "Não, não é nada. Estou indo embora.";
			link.l1.go = "exit";
			break;
		}
		//за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "Capitão, ouvi uns boatos sobre um comboio de prata sendo interceptado...";
				link.l1 = "Você está bem informado, Sr. Knippel.";
				link.l1.go = "HollConvoy_Check";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Wait")
			{
				dialog.text = "Alguma dúvida, capitão?";
				link.l1 = "Não, não é nada. Estou indo embora.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main")
			{
				dialog.text = "Que bom ver você, capitão! Meu comandante, Richard Fleetwood, queria vir aqui pessoalmente para conhecê-lo, mas ontem à noite aconteceu um acidente... Tentaram matar ele bem no meio da rua, uma loucura dessas!";
				link.l1 = "Impossível! O que os guardas estavam fazendo?";
				link.l1.go = "Fleetwood_house";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Perguntas, capitão?";
			link.l1 = "Não, não é nada. Estou indo embora.";
			link.l1.go = "exit";
		break;
		}
			dialog.text = "Ah, corrente de canhão uma ova! O que te trouxe aqui?";
			link.l1 = "Oi, só passei para dar um alô.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------за Голландию--------------------------------------------------	
		case "Dominica":
			dialog.text = "Ah, é mesmo? E como um velho marinheiro, que já pendurou as botas faz tempo, pode te ajudar, camarada?";
			link.l1 = "Veja... Eu sou só um capitão comum e faço viagens regulares entre Martinica e Curaçao. Já fui atacado duas vezes pelo navio fantasma, não muito longe de Martinica... Mas o lance é o seguinte: ela não é nenhum Fata Morgana ou Holandês Voador. Consegui rasgar as velas dela com balas de canhão comuns!";
			link.l1.go = "Dominica_1";			
		break;
		
		case "Dominica_1":
			dialog.text = "É mesmo? Certamente não é típico de um navio fantasma perder velas por causa de balas de canhão, ora essa...";
			link.l1 = "Só sobrevivemos porque meu navio conseguiu fugir, velejando bem rente ao vento. Da última vez, precisei jogar toda a carga ao mar para deixar o casco leve o bastante e escapar... consegue imaginar o prejuízo? Parte o coração!";
			link.l1.go = "Dominica_2";			
		break;
		
		case "Dominica_2":
			dialog.text = "Me derrube, capitão...";
			link.l1 = "Mathias Beck, o governador de Curaçao, simplesmente ignorou minhas reclamações. Disse que as histórias sobre o navio fantasma são bobagem e que meus vigias estavam bêbados de rum. O governador da Martinica prometeu enviar uma patrulha para lá, mas pelo olhar dele, vi que não faria absolutamente nada.  Não posso voltar para a Martinica enquanto aquele maldito pirata 'fantasma' estiver rondando por aí. Meu navio é pequeno, assim como minha tripulação, e é bem provável que não sobrevivamos a um terceiro encontro com ele...";
			link.l1.go = "Dominica_3";			
		break;
		
		case "Dominica_3":
			dialog.text = "É uma pena, amigo. Mas como posso te ajudar?";
			link.l1 = "I heard from the sailors around here that there was a captain in St. John's named Richard Fleetwood who has hunted this same ghost ship. I don't know him personally, which is why I tell this story to you; perhaps you could pass on to him the tale of my misfortunes? I am sure that the filthy pirate is hiding somewhere near the wild shores of Dominica and raiding between Barbados and Martinique.";
			link.l1.go = "Dominica_4";			
		break;
		
		case "Dominica_4":
			dialog.text = "Entre Barbados e Martinica? Ha! Uma rota de comércio gorda e cheia de riquezas. Isso soa exatamente como algo que aquele canalha faria.";
			link.l1 = "Eu não sou rico nem gordo, e não tenho dinheiro para subornar um capitão da marinha por uma escolta militar. Mas, se Sir Fleetwood já está caçando esse rato de porão, poderia, por favor, dizer a ele onde encontrar esse tal 'Holandês Voador'?";
			link.l1.go = "Dominica_5";			
		break;
		
		case "Dominica_5":
			dialog.text = "Você fez muito bem em vir aqui. Vou contar sua história para as pessoas certas, que o diabo leve meu fígado! Em breve, você poderá negociar com a Martinica de novo.";
			link.l1 = "Espero que Deus ouça suas palavras! Obrigado por me ouvir, Charlie. De verdade, espero pelo melhor. Adeus, e cuidado com as balas de corrente!";
			link.l1.go = "Dominica_6";			
		break;
		
		case "Dominica_6":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toDominica";
			AddQuestRecord("Holl_Gambit", "1-17");
			pchar.quest.toDominica.win_condition.l1 = "location";
			pchar.quest.toDominica.win_condition.l1.location = "Dominica";
			pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
			DelMapQuestMarkShore("Shore1");
			DelMapQuestMarkShore("Shore2");
			AddMapQuestMarkIsland("Dominica", true);
		break;

//----------------------------------------------за Англию--------------------------------------------------	
		case "Knippel_check"://начинаем проверять нашего ГГ по всем статьям
			if(makeint(PChar.reputation.nobility) < 48)//низкая репа
			{
				Notification_Reputation(false, 48, "low");
				PlaySound("Voice\English\hambit\Charlie Knippel-04.wav");
				dialog.text = "A velha e boa Inglaterra não precisa dos serviços de canalhas, bala encadeada uma ova! Com todo respeito, vá se foder.";
				link.l1 = "Ei, ei, camarada, cuidado com o que diz ou vou costurar sua boca!";
				link.l1.go = "exit";
				break;
			}
			else
			{
				Notification_Reputation(true, 48, "low");
			}
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 30)//низкая навигация
			{
				dialog.text = "Capitão, vou ser direto. Você não conseguiria sair nem de um saco molhado navegando. Volte quando tiver mais habilidade em navegação, entendeu?";
				// belamour legendary edition покажем критерии  -->
				notification("Skill Check Failed (30)", SKILL_SAILING);
				//<--
				dialog.text = "Cao'n, nossa frota precisa de capitães experientes, não de marujos de primeira viagem. Volte quando tiver dominado a arte da navegação.";							 
				link.l1 = "Entendi... Então, até mais tarde.";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Skill Check Passed", SKILL_SAILING);
			}
			dialog.text = "Ah, você chegou na hora certa, capitão, que corrente de tiro que nada! Richard não sabia em quem podia confiar pra esse serviço arriscado, chegou até a pensar em recusar... Então, parece que os ventos da sorte estão soprando a seu favor hoje. Se você mostrar que está à altura, eu vou recomendar você a um homem muito importante. Tem coragem suficiente pra encarar isso?";
			link.l1 = "Estou carregado com balins, Sr. Knippel.";
			link.l1.go = "Knippel_task";
		break;
		
		case "Knippel_task"://первое задание
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Lucas"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Ah ha! Vejo que o seu ânimo está em alta, capitão! Em breve, o fogo vai começar! Agora preste atenção. A frota de prata da Companhia Holandesa das Índias Ocidentais partiu de Willemstad, em Curaçao, há um ou dois dias. Está a caminho de Philipsburg. Desta vez, há poucos navios na frota. Um único galeão transportando a prata no porão, acompanhado de dois escoltas. Intercepte a frota de prata, capture o Galeão do Leste com a carga de prata e leve-o para Antígua. Pode afundar os escoltas, eles não importam. Acerte os fígados deles com balas de corrente, yar!";
			link.l1 = "Os dias deles estão contados.";
			link.l1.go = "Knippel_task_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_task_1":
			dialog.text = "Um conselho, capitão. A rota de comércio de Curaçao até Sint Maarten passa perto das costas de São Cristóvão. Eu recomendaria preparar uma emboscada por lá. Prepare bem você e seu navio para esse confronto. Enfrentar a Companhia das Índias Ocidentais não é nenhum passeio no parque com uma moça bonita.";
			link.l1 = "Eu sei no que estou me metendo, mas agradeço sua franqueza, Sr. Knippel. Voltarei com a prata holandesa.";
			link.l1.go = "Knippel_task_2";			
		break;
		
		case "Knippel_task_2":
			DialogExit();
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Eng = "true";//признак, что английка уже бралась
			HWICSilverConvoyInWorld();
			AddQuestRecord("Holl_Gambit", "2-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила ,чтобы вышел из архива. 																				   
			pchar.questTemp.HWIC.Eng = "begin";
			SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;
		
		case "HollConvoy_Check"://начинаем проверять
			int iHal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_GALEON_L) iHal++;
				}
			}//признак наличия ТГ в компаньонах
			if (iHal > 0)
			{
				amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
				if (amount <= 0)
				{
					dialog.text = "Não precisa me contar o que aconteceu, capitão. Fiquei sabendo de tudo enquanto o agente da alfândega inspecionava seu navio... Você se saiu muito bem, capitão. Excelente mesmo! Não parecia fácil, bola encadeada coisa nenhuma!";
					link.l1 = "É bom ser reconhecido.";
					link.l1.go = "HollConvoy_complete";
				}
				else
				{
					dialog.text = "Não precisa me contar o que aconteceu. Fui informado de tudo enquanto o agente da alfândega inspecionava seu navio... Você não trouxe toda a prata de volta, que história é essa de bala encadeada! Eu sei exatamente quanto de prata havia naquele navio das Índias Orientais, até o último peso. O objetivo dessa missão não era só testar sua habilidade em combate, mas também sua honestidade. Você falhou nessa última. Saia da minha casa, seu inútil!";
					link.l1 = "Então vá pro inferno, seu idiota!";
					link.l1.go = "HollConvoy_fail";
				}
			}
			else
			{
				dialog.text = "Eu não vejo o navio holandês da Companhia das Índias Orientais no seu esquadrão. Eu disse para você trazê-lo como prêmio. Você vendeu e tentou ficar com o dinheiro para si, é isso?";
				link.l1 = "Espera, era pra eu trazer o navio? Achei que você só queria a prata.";
				link.l1.go = "HollConvoy_noShip";
			}
		break;
		
		case "HollConvoy_noShip":
			dialog.text = "Ninguém faz de bobo o Charlie Knippel! Eu lembro muito bem do que te falei e do que não falei. Você quebrou os termos do nosso acordo, e nenhum inglês decente vai trabalhar com você. Não há lugar para canalhas aqui. Cai fora da minha casa, seu inútil!";
			link.l1 = "Então vá pro inferno, seu idiota!";
			link.l1.go = "HollConvoy_fail";
		break;
		
		case "HollConvoy_fail":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-3");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Eng");//зачищаем для возможности отката к голландскому варианту
			pchar.questTemp.HWIC.Fail2 = "true";
		break;
		
		case "HollConvoy_complete":
			dialog.text = "Venha me visitar amanhã e eu vou apresentá-lo ao meu patrono. Ele vai lhe oferecer mais trabalho à altura das suas habilidades. Além disso, ele vai cuidar do seu... incentivo financeiro. Pode partir!";
			link.l1 = "Muito bem, Sr. Knippel. Estarei aqui amanhã.";
			link.l1.go = "exit";
			npchar.greeting = "knippel_2";
			AddDialogExitQuestFunction("HollConvoy_Remove");
			AddQuestRecord("Holl_Gambit", "2-4");
			SetTimerFunction("EnglandGambit_2_ZadanieStart", 0, 0, 1);
			pchar.questTemp.HWIC.Eng = "Wait";
			AddSimpleRumourCity("They say that you captured a Dutch ship filled with silver. Well done! You are a valiant sailor, captain! Godspeed!", "SentJons", 10, 3, "");
		break;
		
		case "Fleetwood_house":
			dialog.text = "Eu também me pergunto isso... Algum desgraçado jogou pimenta em pó nos olhos do capitão Fleetwood e o apunhalou no peito antes que Richard conseguisse sacar a espada. O assassino queria acabar com o capitão com um só golpe, já que não teria tempo para outro, mas falhou. O capitão Fleetwood sempre usa uma couraça por baixo do casaco\nO canalha, com um tiro de corrente, acertou o fígado dele, conseguiu fugir e se esconder. Parece que ele tem amigos na cidade. O único detalhe de que o capitão se lembra é que o assassino tem só um olho. Não vai ajudar muito, tem muito ciclope vagando pelo cais hoje em dia\nRichard perdeu muito sangue e a pimenta irritou tanto os olhos dele que agora está quase cego...";
			link.l1 = "Pimenta-do-reino? Essa é uma forma cara de cegar alguém. Fleetwood deve ter irritado alguém de verdade. Sinto muito pelo seu capitão. Já descobriram alguma coisa sobre o agressor?";
			link.l1.go = "Fleetwood_house_1";
		break;
		
		case "Fleetwood_house_1":
			dialog.text = "Os fuzileiros do capitão Fleetwood vasculharam a cidade inteira e as baías próximas, mas não encontraram nada, que se danem! Se não conseguimos achá-lo logo após o ataque, agora não há mais esperança de encontrar esse desgraçado. O capitão Fleetwood tem muitos inimigos... Mas, capitão, meu comandante quer vê-lo de qualquer jeito, apesar do ocorrido. Ele está descansando em casa agora, então vamos até lá. Me acompanhe!";
			link.l1 = "Mostre o caminho, Sr. Knippel.";
			link.l1.go = "Fleetwood_house_2";
		break;
		
		case "Fleetwood_house_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			bDisableFastReload = true;//закроем быстрый переход
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
			pchar.quest.Knippel_Outside.win_condition.l1 = "location";
			pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
			pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			sld = characterFromId("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			AddLandQuestMark(sld, "questmarkmain");
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;
		
		case "InFleetwoodHouse":
			dialog.text = "O capitão Fleetwood está lá em cima, no quarto dele. Vá até ele, ele está esperando por você. Eu vou ficar aqui.";
			link.l1 = "Entendido, senhor Knippel. Estou a caminho.";
			link.l1.go = "exit";	
		break;
		
		case "Knippel_ToOfficer":
			dialog.text = "Escute, capitão... O capitão Fleetwood está seguro e em boas mãos agora. Quero ajudar você a se vingar do canalha que o atacou. Ofereço meus serviços como oficial de artilharia. Não sou grande coisa na esgrima, já estou velho pra isso, mas consigo derrubar o mastro de um mercante a mil passos de distância.";
			link.l1 = "Isso eu quero ver. Bem-vindo a bordo, Sr. Knippel!";
			link.l1.go = "Knippel_ToOfficer_1";	
		break;
		
		case "Knippel_ToOfficer_1":
			ForceHeroAutolevel(npchar);
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);//откроем локаторы
			//Книппеля - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 20;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false);//на все дела - 1 месяц
			AddSimpleRumourCity("They say that Sir Richard Fleetwood himself is indebted in you. You are a very important man in our town, sir", "SentJons", 10, 3, "");
		break;
		
		case "hired":
			dialog.text = "Olá, capitão! Precisa de alguma coisa?";
			link.l1 = "Não, nada.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			if (pchar.questTemp.HWIC.Eng == "MirageFail")
			{
				dialog.text = "Você é um completo idiota, chain shot uma ova! Você não conseguiu nem cumprir uma tarefa básica – capturar o 'Mirage' sem perder a 'Valkyrie'\nNossa tripulação não vai mais servir sob seu comando. Temos certeza de que Sir Fleetwood vai aprovar nossa decisão, ele gosta de idiotas tanto quanto a gente.";
				link.l1 = "Vá para o inferno você e seu patrão!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
			{
				dialog.text = "Você é um completo idiota, corrente de bala uma ova! Já perdemos tempo demais resolvendo seus problemas pessoais\nNossa tripulação não vai mais te servir. Temos certeza de que Sir Fleetwood vai aprovar nossa decisão, ele gosta de idiotas tanto quanto a gente.";
				link.l1 = "Vá para o inferno você e seu patrão!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
			{
				dialog.text = "Você é um completo idiota, corrente de bala o cacete! Mandaram você fingir ser um mercador solitário no 'Valkyrie', e o que você fez? Espantou o pirata com a sua flotilha!\nTemos certeza de que Sir Fleetwood vai aprovar nossa decisão, ele gosta de idiotas tanto quanto a gente.";
				link.l1 = "Vá para o inferno você e seu patrão!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake")
			{
				dialog.text = "Você é um completo idiota, bala encadeada uma ova! Resolveu perder nosso tempo fazendo qualquer coisa, menos capturar o 'Mirage' e zarpar para Antígua?\nNossa tripulação não vai mais te servir. Temos certeza de que Sir Fleetwood vai aprovar nossa decisão, ele gosta de idiotas tanto quanto a gente.";
			link.l1 = "Vá para o inferno você e seu patrão!";
			link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)//если сам на Валькирии
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
						{
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "OnCuracao":
			pchar.quest.HWICEng_toBarbadosOver.over = "yes";//снять прерывание
			dialog.text = "Saudações, capitão. Que bom vê-lo!";
			link.l1 = "Saudações, Sr. Knippel. Trouxe o dinheiro? Me entregue e vamos até Willemstad buscar a Abigail. Vai comigo?";
			link.l1.go = "OnCuracao_1";	
		break;
		
		case "OnCuracao_1":
			dialog.text = "Capitão, escute... Não há necessidade de ir a lugar nenhum agora.";
			link.l1 = "Do que você está falando? Isso é um absurdo!";
			link.l1.go = "OnCuracao_2";	
		break;
		
		case "OnCuracao_2":
			dialog.text = "Tenho uma carta do Capitão Fleetwood para você. E o dinheiro. Mas esse dinheiro não é para o pai da Abigail, é para você. Duzentos mil pesos. Leia a carta e tente não julgá-lo com tanta severidade...";
			link.l1 = "O que diabos está acontecendo ultimamente?! Mais uma surpresa desagradável? Me dê a carta!";
			link.l1.go = "OnCuracao_3";	
		break;
		
		case "OnCuracao_3":
			DialogExit();
			NextDiag.CurrentNode = "OnCuracao_4";
			AddMoneyToCharacter(pchar, 200000);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 1;//ещё денек пусть погуляет по пляжу
			pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
			pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol";//патруль в прибрежных водах
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//открыть подземелье
			pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
			AddQuestRecordInfo("LetterFromFleetwood", "1");
			AddQuestRecord("Holl_Gambit", "2-23");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "OnCuracao_4":
			dialog.text = "Você leu, capitão? Vou ser direto. Sinto vergonha do capitão Fleetwood e do que ele fez, disparando bala encadeada contra o próprio... ah, que se dane isso. Rodenburg ficou furioso quando soube do romance da Abigail com o Richard. Patrulhas a pé estão vasculhando Curaçao e há navios militares da Companhia patrulhando estas águas. Precisamos sair daqui o quanto antes.\n Capitão, precisa de um artilheiro? Não faço questão de luxo – só quero uma ração decente de marinheiro, regularmente. Não sou bom de espada, já estou velho pra isso, mas consigo derrubar o mastro de um mercante a mil passos.";
			link.l1 = "Bom, caramba, quero ver você conseguir essa, Sr. Knippel. Bem-vindo à tripulação!";
			link.l1.go = "Knippel_hire";
			link.l2 = "Me arrependo de ter ajudado vocês, canalhas ingleses, desde o começo. Agora não sei mais como sair dessa enrascada. Sigam o próprio caminho, já cansei de surpresas.";
			link.l2.go = "Knippel_exit";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*200;
			npchar.OfficerWantToGo.DontGo = true;
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 120, 120);
			LAi_SetOfficerType(npchar);
			npchar.greeting = "knippel_hire";
			NextDiag.CurrentNode = "Knippel_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			ForceHeroAutolevel(npchar);
			
			//Sinistra - через 2 месяца стартует личный квест Чарли Книппеля "Длинные тени старых грехов"
			SetTimerCondition("DTSG_Start", 0, 0, 60, false);
		break;
		
		case "Knippel_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;
		
//------------------------------------------------против всех-----------------------------------------------
		case "Knippel_abordage":
			dialog.text = "Seu desgraçado! Por que atacou este navio holandês pacífico? Eu não tenho mercadorias valiosas nem ouro, cadeia de balas coisa nenhuma!";
			link.l1 = "Navio holandês? Haha! Não me faça rir, 'holandês'. Ataquei sua bergantim para capturar você, querido Charlie. Bem-vindo ao meu porão de carga. Vamos conversar sobre para onde você estava indo e por quê...";
			link.l1.go = "Knippel_abordage_1";	
		break;
		
		case "Knippel_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-20");
            pchar.quest.Knippel_DieHard.over = "yes";
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "KnippelPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Knippel_prisoner":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			dialog.text = "Você é um demônio, pirata... Vai queimar no inferno por todos os seus pecados! Scre...";
			link.l1 = "Relaxa, pregador. Você fala como um puritano. Melhor cuidar primeiro do estado da sua própria alma.";
			link.l1.go = "Knippel_prisoner_1";
		break;
		
		case "Knippel_prisoner_1":
			dialog.text = "O que você está tramando, canalha? O que você quer do meu comandante e da pobre garota holandesa?";
			link.l1 = "Isso não é da sua conta, Charlie. Não preciso mais de você. Levante-se.";
			link.l1.go = "Knippel_prisoner_2";	
		break;
		
		case "Knippel_prisoner_2":
			dialog.text = "Quer me matar? Bem a sua cara, seu bastardo. *cospe* Maldito seja!";
			link.l1 = "Levanta, Charlie. Faça suas últimas preces.";
			link.l1.go = "Knippel_prisoner_3";	
		break;
		
		case "Knippel_prisoner_3":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
			pchar.quest.RemoveKnippelOver.over = "yes";//снять таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Knippel_officer":
			dialog.text = "Ah, capitão, bala encadeada é o cacete!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "Que eu seja acertado por um balaço, capitão. Nunca mais boto os pés em terra firme. Da última vez que joguei dados na taverna, um desgraçado limpou meus bolsos até o último tostão.";
				Link.l1 = "Ha-ha, tem certeza de que não perdeu tudo no jogo, "+npchar.name+"? Enfim, isso pouco importa... queria conversar com você. Decidi partir para a Europa — como passageiro, num navio alheio. Não sei quando volto. Não peço que me espere aqui. E também não vou te arrastar comigo.";
				Link.l1.go = "SharlieEpilog_Knippel_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Sr. Knippel, estou indo para a antiga e perdida cidade indígena de Tayasal. Quero deixar claro, essa será uma jornada muito perigosa e também fora do comum – precisamos chegar lá através desse... ídolo mágico. Você vem comigo?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Sr. Knippel, me dê um relatório completo sobre o navio.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Quero que você compre certos produtos toda vez que atracarmos.";
				Link.l12.go = "QMASTER_2";
			}
			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Cheguei ao seu comando, Capitão.";
				Link.l2 = "Preciso te dar várias ordens.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Knippel_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Ouça minhas ordens!";
            Link.l1.go = "stay_follow";
			link.l2 = "Não é nada. Dispensado!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Que me afoguem... Os canhões estão em ordem, trocamos os que explodem e mantemos a pólvora seca e segura. Que tipo de relatório você esperava, Capitão? Sou um velho artilheiro, não um intendente. Bala encadeada é o cacete, mas fique sabendo que sou o melhor artilheiro do Caribe!";
			Link.l1 = "Sem discussão aqui, senhor Knippel, você realmente entende do seu ofício. Eu mesmo vou encontrar um intendente, pode ficar tranquilo.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Você quer que o velho Charlie troque o convés de armas pelo de comando? Capitão, eu afundo navios, não negocio cada peso. E tenho certeza de que vão me passar a perna logo na primeira colônia em que tentarmos isso.";
			link.l1 = "Mas é claro, senhor Knippel. Acho que devo começar a procurar um bom intendente.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Estou ouvindo você.";
			Link.l1 = "Isso é sobre abordagens.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Isto é sobre o seu navio.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "Quero que você deixe meu esquadrão por um tempo e vá buscar sua sorte por conta própria.";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Nada até agora.";
			Link.l8.go = "exit";
			break;

		case "Companion_TaskBoarding":
			dialog.Text = "Então, qual é o seu desejo?";
			Link.l1 = "Não aborde navios inimigos. Cuide de si mesmo e da tripulação.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Quero que você aborde navios inimigos.";
			Link.l2.go = "Companion_TaskBoardingYes";
			break;

		case "Companion_TaskChange":
			dialog.Text = "Então, qual é o seu desejo?";
			Link.l1 = "Eu preferiria que você não trocasse de navio depois de embarcar. O seu navio é valioso demais.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Quando você embarca em navios inimigos, pode ficar com eles para você se forem bons.";
			Link.l2.go = "Companion_TaskChangeYes";
			break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Sim, senhor!";
			Link.l1 = "À vontade.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
			break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Vai ser feito.";
			Link.l1 = "À vontade.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
			break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Afirmativo!";
			Link.l1 = "Vai ser feito.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
			break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Vai ser feito.";
			Link.l1 = "À vontade.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
			break;
			//	<========////////////////////////////////////////

		case "stay_follow":
            dialog.Text = "Ordens?";
            Link.l1 = "Fique aqui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Me siga e não fique para trás!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Troque o tipo de munição das suas armas de fogo.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Escolhendo o tipo de munição:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Houve uma mudança de disposição!";
            Link.l1 = "Dispensado.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Houve uma mudança de disposição!";
            Link.l1 = "Dispensado.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Eu acabei me apegando muito a você durante o tempo em que servi, "+pchar.name+", e eu não abandono meu capitão na mão. Se precisar, te sigo até o inferno. Tô contigo!";
			link.l1 = "Obrigado, Sr. Knippel! Fico feliz que eu estava certo sobre você.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Quando vamos começar, que o diabo me leve?";
			link.l1 = "Daqui a pouco. Precisamos nos preparar para isso.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "22");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Эпилог
		case "SharlieEpilog_Knippel_1":
			dialog.text = "Bem, que pena, raio me parta no casco. Pra dizer a verdade, eu até não me importaria de ver a Europa.";
			link.l1 = "Não esperava ouvir isso de você. Pois então, bem-vindo a bordo do pínace '"+GetShipName("Ulysse")+"'! Se quiser, podemos fazer uma visita ao nosso velho conhecido Richard Fleetwood. Acho que você terá algumas palavras pra dizer a ele.";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "Não, senhor. Pro inferno com o Richard. Não quero ouvir falar dele, muito menos ver sua cara.";
			link.l1 = "Como quiser, "+npchar.name+", como quiser. Partimos em duas semanas. Estou planejando uma boa festa de despedida. Espero que você se junte a nós.";
			link.l1.go = "SharlieEpilog_Knippel_3";
		break;

		case "SharlieEpilog_Knippel_3":
			dialog.text = "Que um raio me arrebente o pescoço se eu recusar, capitão!";
			link.l1 = "Excelente. Então nos vemos na taverna depois que eu cuidar de todas as outras coisas.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Knippel = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Você é um "+GetSexPhrase("Ladrão, senhor! Guardas, peguem ele","Ladra, menina! Guardas, peguem ela")+"!!!","Olha só isso! Bastou eu virar as costas e você já foi mexer no meu baú! Peguem o ladrão!!!","Guardas! Roubo! Peguem o ladrão!!!");
			link.l1 = "Maldição!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
