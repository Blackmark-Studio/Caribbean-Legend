void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//вестовой
		case "Regata_Cureer":
			dialog.text = "Bom dia. Você é o capitão "+GetFullName(pchar)+"?";
			link.l1 = "Sim, sou eu. E qual é o problema?";
			link.l1.go = "Regata_Cureer_1";
		break;
		
		case "Regata_Cureer_1":
			dialog.text = "Tenho uma carta para você do governador da Jamaica, Sir Edward D'Oyley.";
			link.l1 = "Uau! Eu não esperava por isso... E o que o governador quer comigo?";
			link.l1.go = "Regata_Cureer_2";
		break;
		
		case "Regata_Cureer_2":
			dialog.text = "Leia a carta, senhor. Resumindo, você está convidado a participar da regata, uma corrida por todo o arquipélago. Os rumores sobre suas habilidades navais e velocidade notável no mar não passaram despercebidos.";
			link.l1 = "Incrível! Bem, eu... eu vou pensar nisso.";
			link.l1.go = "Regata_Cureer_3";
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
			AddQuestRecordInfo("RegataLetter", "1");
		break;
		
		case "Regata_Cureer_3":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = "Além disso, devo lhe conceder acesso livre ao porto de Port Royal. Aqui está uma licença válida por 30 dias. Agora minha missão está cumprida. Adeus, capitão.";
				link.l1 = "Obrigado. A licença é muito bem-vinda. Adeus!";
				link.l1.go = "Cureer_exit";
				GiveNationLicence(HOLLAND, 30);
			}
			else
			{
				dialog.text = "Ótimo. Agora minha missão está completa. Adeus, Capitão.";
				link.l1 = "Adeus!";
				link.l1.go = "Cureer_exit";
			}
		break;
		
		case "Cureer_exit":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.Regata.ToPortRoyal = "true";
			SetQuestHeader("Regata");
			AddQuestRecord("Regata", "1");
		break;
		
		//распорядитель регаты
		case "Regata_Head":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Bom dia. Você vai participar da regata, certo?";
				link.l1 = "Exatamente, senhor. Meu nome é "+GetFullName(pchar)+". Recebi o convite.";
				link.l1.go = "Regata_Head_1";
			}
			else
			{
				dialog.text = "Quer alguma coisa, senhor?";
				link.l1 = "Não, não é nada. Já estou indo embora.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_1":
			iTest = FindColony("PortRoyal"); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				dialog.text = "Fico feliz em conhecê-lo, Capitão "+GetFullName(pchar)+". Então vamos começar. Você já sabe o básico pela carta, certo? Só luggers, e ela deve ser o único navio na sua esquadra para participar da regata. Cumpriu esses requisitos?";
				// belamour legendary edition допускаем курьерский люггер 
				ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
				if((GetCompanionQuantity(pchar) > 1) || !ok)
				{
					link.l1 = "Ainda não. Vou fazer isso agora e volto já.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
				else
				{
					link.l1 = "Sim, eu tenho.";
					link.l1.go = "Regata_Head_2";
				}
			}
			else
			{
				dialog.text = "Você veio participar da regata, mas onde está o seu navio, capitão?";
				link.l1 = "Com licença, senhor. Vou trazer meu navio ao porto imediatamente.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head_repeat";
			}
		break;
		
		case "Regata_Head_repeat":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				iTest = FindColony("PortRoyal"); 
				if (iTest != -1)
				{
					rColony = GetColonyByIndex(iTest);
				}
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
				{
					ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
					dialog.text = "Ah, é você de novo. Já fez tudo o que precisava para cumprir os requisitos da regata?";
					// belamour legendary edition допускаем курьерский люггер 
					if ((GetCompanionQuantity(pchar) > 1) || !ok)
					{
						link.l1 = "Ainda não. Vou fazer isso agora e volto já.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Regata_Head_repeat";
					}
					else
					{
						link.l1 = "Sim, eu tenho.";
						link.l1.go = "Regata_Head_2";
					}
				}
				else
				{
					dialog.text = "Capitão, não temos nada para conversar até que eu veja seu navio ancorado. Entendeu, ou preciso repetir?";
					link.l1 = "Com licença, senhor. Vou trazer meu navio ao porto imediatamente.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
			}
			else
			{
				dialog.text = "Quer alguma coisa, senhor?";
				link.l1 = "Não... não é nada. Já estou indo embora.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_2":
			dialog.text = "Certo. Agora, o próximo item. Qual é o nome do seu navio?";
			link.l1 = "'"+pchar.Ship.Name+"'.";
			link.l1.go = "Regata_Head_3";
		break;
		
		case "Regata_Head_3":
			dialog.text = "Como a regata é organizada pelas autoridades inglesas e existem regras fixas, o nome do seu navio precisa ser alterado durante o evento. Não se preocupe, isso vale para todos os participantes.";
			link.l1 = "Dizem que dá azar mudar o nome do seu navio.";
			link.l1.go = "Regata_Head_4";
		break;
		
		case "Regata_Head_4":
			dialog.text = "Você pode mudar o nome de volta depois da regata. Então, seu lugre vai se chamar 'Santa Catarina'.";
			link.l1 = "Entendi, senhor. Vou mudar o nome.";
			link.l1.go = "Regata_Head_5";
			pchar.Ship.Name = "Saint Catherine";
		break;
		
		case "Regata_Head_5":
			dialog.text = "Agora vamos falar sobre a própria regata. Preste atenção. Também vou te entregar um papel com as regras.\nA regata começa e termina em Port Royal. São cinco pontos que você terá que alcançar\nO primeiro é de Port Royal até Belize, West Main\nO segundo é de Belize até Port-au-Prince, Hispaniola\nO terceiro é de Port-au-Prince até St. John's, Antigua\nO quarto é de St. John's até Bridgetown, Barbados\nE o último é de Bridgetown até Port Royal\nFui claro?";
			link.l1 = "Perfeitamente claro, senhor.";
			link.l1.go = "Regata_Head_6";
		break;
		
		case "Regata_Head_6":
			dialog.text = "Excelente. Você deve se apresentar no escritório portuário de cada uma das seguintes cidades: Belize, Port-au-Prince, St. John's, Bridgetown. Você será desclassificado se deixar de passar por alguma dessas cidades ou se não seguir a ordem correta\nOs escritórios ficarão abertos vinte e quatro horas durante toda a regata. Bata na porta e eles vão deixar você entrar.";
			link.l1 = "Entendido.";
			link.l1.go = "Regata_Head_7";
		break;
		
		case "Regata_Head_7":
			dialog.text = "É proibido trocar de navio ou adicionar mais navios ao seu esquadrão. Isso será verificado em cada cidade, então fique atento a isso.";
			link.l1 = "Vou pensar nisso. Quem geralmente é considerado o vencedor, e podemos falar sobre prêmios?";
			link.l1.go = "Regata_Head_8";
		break;
		
		case "Regata_Head_8":
			dialog.text = "Há apenas um vencedor na regata – o capitão cujo navio chegar primeiro a Port Royal. O prêmio é muito valioso. O vencedor receberá uma grande quantia – 250.000 pesos. Além disso, ele ganhará um conjunto de presentes valiosos.";
			link.l1 = "Então, os perdedores não ganham nada?";
			link.l1.go = "Regata_Head_9";
		break;
		
		case "Regata_Head_9":
			dialog.text = "Exatamente. Além disso, muitos cidadãos ricos e pobres das colônias inglesas apostam no vencedor da regata. Você também pode apostar... em si mesmo. Normalmente, todo capitão faz isso. Se ganhar, vai lucrar ainda mais—sem falar na motivação extra. Geralmente, sou eu quem recebe as apostas. Vai apostar na sua própria vitória?";
			link.l1 = "Ha! Claro que estou. Quanto posso apostar?";
			link.l1.go = "Regata_rate";
			link.l2 = "Vou pensar nisso. Talvez eu faça uma aposta.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_Head_10":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Pense se quiser. Você ainda tem um tempo antes da regata começar.";
				link.l1 = "Certo. Quando começa?";
				link.l1.go = "Regata_Head_11";
				DeleteAttribute(pchar, "questTemp.Regata.Rate");
				pchar.questTemp.Regata.Ratenext = "true";
			}
			else
			{
				dialog.text = "Pense se quiser. Você ainda tem um tempo antes da regata começar.";
				link.l1 = "Tudo bem.";
				link.l1.go = "exit";
			}
		break;
		
		case "Regata_Head_11":
			CreateRegataAdversaries();
			dialog.text = "Daqui a três dias, ao meio-dia em ponto. Venha ao cais e não se atrase. Você terá cinco concorrentes.\n"+pchar.questTemp.Regata.AdversaryName.a+", do "+pchar.questTemp.Regata.AdversaryShipName.a+"\n"+pchar.questTemp.Regata.AdversaryName.b+", do(a) "+pchar.questTemp.Regata.AdversaryShipName.b+"\n"+pchar.questTemp.Regata.AdversaryName.c+", do "+pchar.questTemp.Regata.AdversaryShipName.c+"\n"+pchar.questTemp.Regata.AdversaryName.d+", do(a) "+pchar.questTemp.Regata.AdversaryShipName.d+"\n"+pchar.questTemp.Regata.AdversaryName.e+", do(a) "+pchar.questTemp.Regata.AdversaryShipName.e+"\nTodos eles são capitães experientes. Bem, acho que é isso. Pegue a folha com as regras, só por precaução. Te vejo na largada!";
			link.l1 = "Adeus, senhor.";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND) link.l1.go = "Regata_Head_13";
			else link.l1.go = "Regata_Head_12";
		break;
		
		case "Regata_Head_12":
			DialogExit();
			pchar.quest.RegataToPortRoyalTimeOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
			pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
			pchar.quest.Regata_Lost.win_condition.l1.date.hour  = 13.0;
			pchar.quest.Regata_Lost.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Lost.function = "Regata_Lost";
			pchar.quest.Regata_Start.win_condition.l1 = "Timer";
			pchar.quest.Regata_Start.win_condition.l1.date.hour  = 12.0;
			pchar.quest.Regata_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l2 = "locator";
			pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
			pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
			pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
			pchar.quest.Regata_Start.function = "Regata_Start";
			AddQuestRecordInfo("RegataRules", "1");
			NextDiag.CurrentNode = "Regata_Prepare";
			DeleteAttribute(pchar, "questTemp.Regata.Begin");
			pchar.questTemp.Regata.Prepare = "true";
			AddQuestRecord("Regata", "2");
		break;
		
		case "Regata_Head_13":
			dialog.text = "Espere! Vou te dar uma licença de 30 dias para visitar portos ingleses e franceses. A regata não vai durar mais que um mês. Por favor, aceite.";
			link.l1 = "Obrigado!";
			link.l1.go = "Regata_Head_12";
			GiveNationLicence(HOLLAND, 30);
		break;
		
		case "Regata_rate":
			dialog.text = "Quanto você está apostando?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Regata_rate_1";
			link.l2 = "Acho que ainda preciso de um tempo para pensar.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_1":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Regata.Rate = sti(iQty);
			if (iQty < 10000)
			{
				dialog.text = "Senhor, isso não tem graça, nem é brincadeira. Não vou trabalhar por uma quantia tão pequena.";
				link.l1 = "Me desculpe... Vamos reconsiderar a aposta.";
				link.l1.go = "Regata_rate";
				break;
			}
			if (iQty > 100000)
			{
				dialog.text = "Senhor, não posso aceitar uma aposta tão alta por causa das regras da regata. Reduza para um valor razoável.";
				link.l1 = "Que pena. Vamos repensar o valor.";
				link.l1.go = "Regata_rate";
				break;
			}
			dialog.text = ""+iQty+"? Essa é uma bela aposta. Estou pronto para aceitá-la. Seu dinheiro, senhor?";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
			{
				link.l1 = "Por favor, aceite.";
				link.l1.go = "Regata_rate_2";
			}
			link.l2 = "Não tenho moedas suficientes agora. Vou voltar depois e a gente faz uma aposta. E vou pensar melhor, talvez eu mude de ideia sobre o valor.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
			pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate)*(1.5+frand(1.5)); // dlc
			dialog.text = "Splendid! Now all you need to do is be the first, and the prize will be yours. Its final value may vary; it all depends on how many people stake on you in the end.";
			if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
			{
				link.l1 = "Entendi. Quando começa a regata?";
				link.l1.go = "Regata_Head_11";
			}
			else
			{
				link.l1 = "Entendi. Vou esperar pelo começo. Até mais!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
				NextDiag.TempNode = "Regata_Prepare";
			}
		break;
		
		case "Regata_Prepare":
			dialog.text = "Ah, você está aqui de novo, capitão "+GetFullName(pchar)+"? O que você quer?";
			if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
			{
				link.l1 = "Quero apostar na minha vitória.";
				link.l1.go = "Regata_rate";
			}
			link.l2 = "Não, não é nada. Só queria te cumprimentar.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Regata_Prepare";
		break;
		
		//старт регаты
		case "Regata_CitMan":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Capitão, é a sua primeira vez? Deixe-me te dizer, é bom tomar cuidado. Seus concorrentes podem ter algumas surpresas bem desagradáveis guardadas para você...","Capitão, apostei tudo em você. Não me decepcione!","Capitão, os moradores dos portos da regata podem te oferecer algo para comprar. Muitas vezes pode ser bem útil. Pense nisso."),LinkRandPhrase("Tenha uma viagem segura, capitão!","Capitão, por favor, tenha cuidado, os castelhanos costumam caçar os barcos pequenos de quem navega em águas espanholas.","Ouvi dizer que alguns tipos suspeitos costumam oferecer seus 'serviços' aos capitães da regata. Cabe a você decidir se aceita ou não as propostas deles."));
			link.l1 = "Sim, sim, claro... obrigado, eu acho.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitMan";
		break;
		
		case "Regata_CitWom":
			dialog.text = LinkRandPhrase("Capitão, meu marido e eu apostamos dez mil na sua vitória. Não nos decepcione! Vou rezar por você!","Capitão! Desejo-lhe boa sorte!","Uhm... você é um capitão tão bravo e corajoso...");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitWom";
		break;
		
		case "Regata_CitHorse":
			dialog.text = LinkRandPhrase("Ei, marinheiro! Acene para a beleza! Estarei esperando sua volta!","Ei, marinheiro corajoso! A madame disse que vai me dar de prêmio para o vencedor da regata, de graça... Tenta ganhar, você é tão bonito!","Não esqueça de nos visitar quando voltar, bonitão, vamos te satisfazer do jeito mais caprichado!");
			link.l1 = "Bem, hah... Vou pensar nisso, obrigado!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitHorse";
		break;
		
		case "Regata_Prepare_1":
			if (sti(environment.time) < 12.0)
			{
				dialog.text = "Capitão, a regata começa ao meio-dia. Pode descansar agora, estamos preparando as festividades. Volte ao meio-dia, seus concorrentes farão o mesmo.";
				link.l1 = "Muito bem, senhor! Estarei esperando pelo começo...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Aqui está, capitão.";
				link.l1 = "Minha tripulação e eu estamos prontos, senhor! Estou aguardando o sinal...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_Prepare_1";
		break;
		
		case "Regata_Start":
			dialog.text = "Então, senhores, aqui estamos nós. Declaro a regata aberta. Vocês conhecem as regras. Quem voltar aqui primeiro será celebrado como vencedor. Senhoras e senhores, vamos desejar boa sorte aos nossos valentes capitães!\nSenhores! Estão prontos? Prontos! Preparar! Já!";
			link.l1 = "...";
			link.l1.go = "Regata_Start_1";
		break;
		
		case "Regata_Start_1":
			DialogExit();
			PlaySound("people fight\mushketshot.wav");
			log_info("The regatta has started! Get aboard! Head to Belize!");
			for (i=1; i <=5; i++)
			{
				sld = characterFromId("Regata_Cap_F"+i);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			Island_SetReloadEnableGlobal("Jamaica", false);//на остров нельзя
			SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);//таймер на возврат нормы
			LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//откроем выход в море
			DeleteAttribute(pchar, "questTemp.Regata.Prepare");
			pchar.questTemp.Regata.Go = "true";
			pchar.questTemp.Regata.Town = "Beliz";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
			pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
			sld = characterFromId("Beliz_shipyarder");
			LAi_RemoveLoginTime(sld);
			AddQuestRecord("Regata", "3");
		break;
		//старт регаты
		
		//верфист с парусами
		case "Regata_Shipyarder":
			dialog.text = "Saudações, capitão! Fiquei sabendo que você está participando da regata do Caribe.";
			link.l1 = "É verdade. As notícias realmente se espalham pelo arquipélago mais rápido que o vento.";
			link.l1.go = "Regata_Shipyarder_1";
		break;
		
		case "Regata_Shipyarder_1":
			dialog.text = "Eles têm sim, capitão. Tenho uma proposta para você. É sobre o seu navio e a regata.";
			link.l1 = "Heh! Interessante. Estou ouvindo você, senhor.";
			link.l1.go = "Regata_Shipyarder_2";
		break;
		
		case "Regata_Shipyarder_2":
			dialog.text = "Tenho um jogo de velas perfeitas para um lugre, feitas do melhor algodão. Essas velas vão aumentar a aceleração do seu navio e te dar vantagem de tempo sobre os seus rivais\nEstou pronto para vendê-las a você, se é isso que deseja.";
			link.l1 = "Quanto você quer por essas velas?";
			link.l1.go = "Regata_Shipyarder_3";
		break;
		
		case "Regata_Shipyarder_3":
			dialog.text = "Apenas 15.000 pesos. Você há de concordar que é um preço bem modesto para uma... situação como esta.";
			if (makeint(Pchar.money) >= 15000)
			{
				link.l1 = "Concordo. Estou comprando essas velas novas para o meu lugre. Aqui, pegue seu dinheiro, senhor. Você poderia ser gentil e entregá-las no meu navio enquanto faço o check-in?";
				link.l1.go = "Regata_Shipyarder_4";
			}
			link.l2 = "Eu não tenho esse tipo de dinheiro. Então não vou poder comprar suas velas.";
			link.l2.go = "Regata_Shipyarder_exit";
		break;
		
		case "Regata_Shipyarder_4":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "Vai ser feito, senhor. Meus homens só estão esperando a ordem, e eu lhe garanto que não vai se arrepender. Além disso, essas velas têm um belo tom de azul. Sua bela vai gostar.";
			link.l1 = "Então tá! Bem, eu preciso ir e você cuida das velas.";
			link.l1.go = "Shipyarder_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp))+12;//выиграл 12 часов у всех
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
			}
			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
			SetSailsColor(Pchar, 5);
			AddQuestRecord("Regata", "28");
		break;
		
		case "Regata_Shipyarder_exit":
			dialog.text = "Que pena. Bem, é sua escolha. Adeus, capitão.";
			link.l1 = "Adeus!";
			link.l1.go = "Shipyarder_exit";
			pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d)-16;//четвертый соперник выиграл 16 часов
			log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
			AddQuestRecord("Regata", "29");
		break;
		
		case "Shipyarder_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
		break;
		//верфист с парусами
		
		//контрики с пушками
		case "Regata_Contra":
			dialog.text = "Olá, Capitão "+GetFullName(pchar)+". Precisamos falar com você... na verdade, é só uma... proposta de negócio.";
			link.l1 = "Hm. Interessante, e como você sabe quem eu sou?";
			link.l1.go = "Regata_Contra_1";
		break;
		
		case "Regata_Contra_1":
			dialog.text = "O que posso dizer, sempre disseram que eu era talentoso... Ha-ha, bom, a Regata está a todo vapor e você está participando dela, você é um Capitão famoso!";
			link.l1 = "Entendi. Bem, diga o que pensa.";
			link.l1.go = "Regata_Contra_2";
		break;
		
		case "Regata_Contra_2":
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				sTemp = pchar.questTemp.Regata.ContraIndex;
				dialog.text = "Estamos cientes de que há mais um participante à sua frente - "+pchar.questTemp.Regata.AdversaryName.(sTemp)+" do "+pchar.questTemp.Regata.AdversaryShipName.(sTemp)+". Ele deixou o porto há pouco tempo, e logo estará navegando além do Cabo Gonaives.";
			}
			else
			{
				dialog.text = "Estamos cientes de que há mais um participante bem atrás de você - "+pchar.questTemp.Regata.AdversaryName.b+" do(a) "+pchar.questTemp.Regata.AdversaryShipName.b+". Ele vai estar aqui em algumas horas.";
			}
			link.l1 = "Hmm... você está muito bem informado.";
			link.l1.go = "Regata_Contra_3";
		break;
		
		case "Regata_Contra_3":
			if (sti(pchar.questTemp.Regata.Index != 1)) sTemp = "letting you pass ahead of him and take his position";
			else sTemp = "therefore you will be taking a lead for a long time";
			dialog.text = "Com certeza. Agora vamos direto ao ponto. Oferecemos nossa ajuda em troca do seu dinheiro. Colocamos quatro canhões do nosso navio no cabo atrás da Baía de Gonaives. Qualquer navio da regata precisa passar por lá\nOs canhões estão carregados com balas encadeadas. Se fecharmos negócio, vou avisar nossos amigos artilheiros para arruinarem as velas do seu concorrente, assim ele vai ser obrigado a perder tempo consertando tudo, "+sTemp+".";
			link.l1 = "Quanto você quer por esse serviço?";
			link.l1.go = "Regata_Contra_4";
			link.l2 = "Não. Não vou usar esses métodos para vencer. Você se enganou sobre mim. Adeus, senhores.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_exit":
			dialog.text = "Bem, capitão, a escolha é sua. Adeus.";
			link.l1 = "Obrigado pela informação sobre o cabo. Vou manter distância dele.";
			link.l1.go = "Contra_exit";
			AddQuestRecord("Regata", "31");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Regata_Contra_4":
			if (sti(pchar.questTemp.Regata.Index != 1)) iTemp = 50000;
			else iTemp = 30000;
			dialog.text = "Não muito. Só "+iTemp+" pesos. E um dos seus concorrentes vai perder quase dois dias por causa de... um acidente, ha-ha!";
			if (makeint(Pchar.money) >= iTemp)
			{
				link.l1 = "Heh! Você fala com razão, meu amigo! Eu estou pagando. Mas que garantias eu tenho de que você vai cumprir sua parte? E que não vai atirar no meu navio quando eu passar pelo cabo?";
				link.l1.go = "Regata_Contra_5";
			}
			link.l2 = "Eu não tenho esse tipo de dinheiro. Então não vou poder usar seus serviços.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_5":
			dialog.text = "Capitão, por favor, nós somos contrabandistas, não piratas. Somos todos homens honestos... à nossa maneira. Você já deve ter usado nossos serviços antes, certo? Dou minha palavra. Pode confiar nela.";
			link.l1 = "Justo, tudo bem, pegue seu dinheiro.";
			link.l1.go = "Regata_Contra_6";
		break;
		
		case "Regata_Contra_6":
			AddQuestRecord("Regata", "30");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "Você vai ficar satisfeito com esse acordo, capitão. E vou avisar meus rapazes do canhão sobre isso imediatamente. Boa sorte!";
			link.l1 = "O mesmo pra você...";
			link.l1.go = "Contra_exit";
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				AddMoneyToCharacter(pchar, -50000);
				sTemp = pchar.questTemp.Regata.ContraIndex;
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp))+48;//задержка на 48 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
			}
			else
			{
				AddMoneyToCharacter(pchar, -30000);
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b)+36;//задержка на 36 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
			}
		break;
		
		case "Contra_exit":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("RegataContra_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
			}
		break;
		//контрики с пушками
		
		//падре
		case "Regata_Padre":
			pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
			dialog.text = "Bom dia para você, meu filho. Quero cumprimentá-lo e humildemente perguntar: gostaria de contribuir para o tesouro da paróquia como um fiel servo da Inglaterra e de nosso grande Senhor?";
			link.l1 = "Padre, as pessoas fazem caridade porque sentem isso na alma, não por obrigação. Estou começando a achar que todo mundo no arquipélago resolveu roubar os capitães da regata...";
			link.l1.go = "Regata_Padre_exit";
			link.l2 = "Claro, padre. Quanto seria suficiente?";
			link.l2.go = "Regata_Padre_1";
		break;
		
		case "Regata_Padre_1":
			dialog.text = "Tanto quanto seus desejos e possibilidades permitirem, meu filho. Nossa paróquia será grata até pela menor quantia.";
			Link.l1.edit = 4;			
			link.l1 = "";
			link.l1.go = "Regata_Padre_2";
		break;
		
		case "Regata_Padre_2":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Essa não é a atitude certa, meu filho. Todos nós temos pecados, não se esqueça da sua alma. Você vai ter que se apresentar diante do nosso Criador... e talvez em breve.";
				link.l1 = "Não preciso dos seus sermões, padre. Adeus.";
				link.l1.go = "Padre_exit";
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				AddQuestRecord("Regata", "35");
				break;
			}
			if (iTemp > 0 && iTemp <= 1000)//ничего не скажет
			{
				dialog.text = "A nossa paróquia e eu agradecemos por este modesto presente.";
				link.l1 = "Seja bem-vindo, padre.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "35");
			}
			if (iTemp > 1000 && iTemp <= 5000)//1 категория - намекнет
			{
				dialog.text = "A nossa paróquia e eu agradecemos por este presente. E quero te alertar, meu filho, que alguns homens pecadores planejam te fazer mal. Tome cuidado no mar!";
				link.l1 = "Padre, todo dia tem gente tramando alguma coisa contra mim... Mas obrigado por se preocupar com o meu destino.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "34");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 5000 && iTemp <= 10000)//2 категория - скажет
			{
				dialog.text = "Agradeço, em nome da nossa paróquia, por este valioso presente. Em troca, quero lhe alertar que algumas pessoas realmente perversas estão conspirando contra você. Ouvi dizer que esses apóstatas vis querem afundar seu navio bem aqui neste porto\nEles já prepararam um navio cheio de pólvora para esse ato maligno. Tome cuidado, meu filho, essas almas perdidas estão mesmo decididas em seus intentos... Que Deus te abençoe!";
				link.l1 = "Obrigado, padre. Vou ficar atento.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "33");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 10000)//3 категория - расскажет полностью
			{
				dialog.text = "Você é muito generoso, meu filho. A humildade de um simples servo de Deus não me permite aceitar toda a quantia que você está disposto a doar para o bem da nossa igreja. Aceitarei apenas 10.000 pesos\nEm troca, quero lhe alertar que pessoas perversas estão conspirando contra você. Ouvi dizer que esses apóstatas vis estão planejando afundar seu navio bem aqui neste porto\nEles prepararam uma chalupa cheia de pólvora chamada '"+pchar.questTemp.Regata.BranderName+"', ela está navegando sob a bandeira inglesa para se aproximar de você sem levantar suspeitas. Tome cuidado, meu filho, essas almas perdidas levam a sério suas intenções vis.  Destrua-os, eu lhe concedo absolvição por esse pecado. Que Deus te abençoe! Vou rezar por você, meu filho.";
				link.l1 = "Obrigado, padre santo. Se esses desgraçados ousarem fazer qualquer maldade, eu mando todos direto pro inferno!";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -10000);
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddQuestRecord("Regata", "32");
				AddQuestUserData("Regata", "sText", pchar.questTemp.Regata.BranderName);
			}
		break;
		
		case "Regata_Padre_exit":
			dialog.text = "Não se irrite, meu filho. A raiva é um pecado. Você tem o direito de não fazer caridade. Vá em paz, meu filho.";
			link.l1 = "Adeus, padre santo.";
			link.l1.go = "Padre_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddQuestRecord("Regata", "35");					  
		break;
		
		case "Padre_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
		break;
		
		case "Regata_Spyglass":
			dialog.text = "Bom dia para você, capitão! Meu nome é "+npchar.name+" e eu gostaria de...";
			link.l1 = "... para me oferecer algo... Estou certa, mocinha?";
			link.l1.go = "Regata_Spyglass_1";
		break;
		
		case "Regata_Spyglass_1":
			dialog.text = "Claro, capitão! E por que essa surpresa? Você é um marinheiro bonito e vai participar da regata, então todo mundo está disposto a te vender alguns itens náuticos úteis.";
			link.l1 = "Certo, beleza, você tem razão. O que você tem pra mim?";
			link.l1.go = "Regata_Spyglass_2";
		break;
		
		case "Regata_Spyglass_2":
			if(hrand(11) > 10)//отличная труба
			{
				pchar.questTemp.Regata.Spy = "spyglass4";
				sTemp = "an excellent spyglass";
				pchar.questTemp.Regata.SpyPrice = 20000;
				pchar.questTemp.Regata.SpyIndex = 12;//выигрыш - 12 часов
			}
			else
			{
				if(hrand(11) < 6)//обычная труба
				{
					pchar.questTemp.Regata.Spy = "spyglass2";
					sTemp = "an ordinary spyglass";
					pchar.questTemp.Regata.SpyPrice = 1800;
					pchar.questTemp.Regata.SpyIndex = 4;//выигрыш - 4 часа
				}
				else//хорошая труба - как пригодится
				{
					pchar.questTemp.Regata.Spy = "spyglass3";
					sTemp = "a good spyglass";
					pchar.questTemp.Regata.SpyPrice = 10000;
					pchar.questTemp.Regata.SpyIndex = 8;//выигрыш - 8 часов
				}
			}
			dialog.text = "Aqui, dê uma olhada. Herdei isso do meu pai. Ele era marinheiro, assim como você, e tinha muitos instrumentos de navegação. Eu não preciso disso, mas tenho certeza de que será útil para você. Só peço "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" por isso.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
			{
				link.l1 = "Ora, ora..."+sTemp+"! Interessante! Eu digo, vou comprar de você. Pelos seus lindos olhos. Então, você quer "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" por isso? Por favor, pegue seu dinheiro.";
				link.l1.go = "Regata_Spyglass_3";
			}
			link.l2 = "Hm..."+sTemp+"? Não, garota, me desculpe, mas não preciso disso. Já tenho uma luneta muito boa comigo. Então... que pena!";
			link.l2.go = "Regata_Spyglass_exit";
		break;
		
		case "Regata_Spyglass_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
			GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
			dialog.text = "Obrigado, capitão. Espero que lhe seja útil. Fico feliz que tenha achado útil. Boa sorte na regata!";
			link.l1 = "Obrigado, "+npchar.name+"! Adeus.";
			link.l1.go = "Spyglass_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp))+sti(pchar.questTemp.Regata.SpyIndex);//купил трубу - выиграл время
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
		break;
		
		case "Regata_Spyglass_exit":
			dialog.text = "Que pena, capitão. Eu esperava que fosse útil para você. Bem, vou tentar vender para outra pessoa. Adeus!";
			link.l1 = "Adeus, "+npchar.name+".";
			link.l1.go = "Spyglass_exit";
			pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c)-sti(pchar.questTemp.Regata.SpyIndex);//третий соперник выиграл время
		break;
		
		case "Spyglass_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "Regata_SiegeOfficer":
			dialog.text = "Saudações, capitão. Você não é um dos participantes da regata? Acertei?";
			link.l1 = "Sim. E qual é o acordo, oficial?";
			link.l1.go = "Regata_SiegeOfficer_1";
		break;
		
		case "Regata_SiegeOfficer_1":
			dialog.text = "Você já deve saber que nossa colônia está sob cerco espanhol. Por isso nosso governador deseja falar com você. Poderia fazer a gentileza de visitá-lo? O assunto é muito urgente.";
			link.l1 = "Hm... Muito bem, irei ver Sua Excelência imediatamente, embora eu realmente não entenda como poderia estar envolvido nas operações militares.";
			link.l1.go = "Regata_SiegeOfficer_2";
		break;
		
		case "Regata_SiegeOfficer_2":
			dialog.text = "Você está envolvido, capitão. Não vamos perder tempo, vamos direto para a residência. Siga-me.";
			link.l1.go = "Regata_SiegeOfficer_3";
		break;
		
		case "Regata_SiegeOfficer_3":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
		break;
		
		case "Regata_SiegeOfficer_4":
			dialog.text = "Senhor! Estou pronto para enviar os civis para o seu navio. Vamos agora?";
			link.l1 = "Sim, claro. Vamos zarpar imediatamente. Diga ao pessoal para embarcar nos botes.";
			link.l1.go = "Regata_SiegeOfficer_5";
		break;
		
		case "Regata_SiegeOfficer_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
			}
		break;
		
		case "Regata_SiegeOfficer_6":
			dialog.text = "Conseguimos... Parece que esse saveiro era um batedor do esquadrão e esses desgraçados castelhanos estavam farejando por aqui. Capitão, por favor, me ajude a levar as mulheres para as cavernas, pode ser que haja mais destacamentos espanhóis.";
			link.l1 = "Certo. Vamos!";
			link.l1.go = "Regata_SiegeOfficer_7";
		break;
		
		case "Regata_SiegeOfficer_7":
			DialogExit();
			sld = characterFromId("SiegeOfficer");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_SiegeOfficer_8":
			dialog.text = "Gratitude for your help, captain! If it weren't for you and your courage... You are a true hero; you completed this operation despite all dangers and your own interests. I have been thinking about how to reward you... and there is a way to improve your chances in the regatta.";
			link.l1 = "Interessante. E qual é esse jeito?";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_Hovernor":
			dialog.text = "Saudações, capitão "+GetFullName(pchar)+". Que bom que você veio. Nossa cidade precisa da sua ajuda.";
			link.l1 = "Senhor, se está falando sobre o esquadrão espanhol que está atacando sua colônia neste exato momento, então não faço ideia de como posso ajudá-lo. Eu comando uma escuna, não um navio de linha...";
			link.l1.go = "Regata_Hovernor_1";
		break;
		
		case "Regata_Hovernor_1":
			dialog.text = "Listen to me, captain, and you will understand. We are in serious trouble. The city is under Spanish siege. A decisive battle for the fort is about to begin. Besides, a few hundred Spaniards have already landed and blocked every exit from the city; now they can attack us from both sea and land\nThe fort's garrison is preparing to defend the city from the squadron, and there are not enough soldiers in the settlement itself. Every man capable of handling a weapon is mobilised, but what about the others?\nThere are a hundred souls of women in Bridgetown. Can you imagine what will happen to them if we fail to protect our colony? I believe that you understand.";
			link.l1 = "Senhor, eu entendo o que está dizendo, mas de novo, como posso ajudar? O que espera de mim? Que eu enfrente navios de guerra, ou que coloque minha tripulação na milícia da cidade?";
			link.l1.go = "Regata_Hovernor_2";
		break;
		
		case "Regata_Hovernor_2":
			switch (sti(Pchar.BaseNation))
			{
				case ENGLAND: sTemp = "You are English , help us to save English citizens and what is important - women!" break;
				case FRANCE: sTemp = "You are French, so you basically are our ally, help us to save English citizens and what is more important - women!" break;
				case SPAIN: sTemp = "I know that you are Spanish and these are your people in the sea, so I know that I am already asking for a lot, but these women are innocent and have nothing to do with this battle. So please I beg of you, help them!" break;
				case HOLLAND: sTemp = "I know that you are Dutch and our nations are at war, but you are participating in the English regatta under the English flag. Don't you think that it is right to fight for innocent and peaceful people, for women? Please captain, help them!" break;
			}
			dialog.text = "Neither. I ask only one thing of you. Take the women and children away from here on your ship. There are not many of them, about a hundred. Take them to Harrison Cape along with Lieutenant Mahony; he will make sure they are safe in the cave\nI am sure the Spanish won't search for them. I have no ships to spare; everything we had was sunk by the Spanish squadron. You are my last hope. You can take them to the cape in a single voyage, even though your vessel will be overloaded. Ships of the line won't follow you.\nI can't ask anyone else to do it. "+sTemp+"";
			link.l1 = "Senhor, me desculpe, mas meu navio já está sobrecarregado e não vai aguentar tanta gente, nem mesmo em duas viagens. Qualquer bala de canhão que cair por perto pode afundar meu navio e suas mulheres no fundo do mar. Me perdoe, mas não posso ajudar.";
			link.l1.go = "Regata_Hovernor_exit";
			link.l2 = "Muito bem, senhor. Vou ajudá-lo. A honra de um marinheiro me obriga a isso.";
			link.l2.go = "Regata_Hovernor_3";
		break;
		
		case "Regata_Hovernor_3":
			dialog.text = "Fico feliz que tenha aceitado. Você é um verdadeiro soldado. O tenente Mahony vai trazer as mulheres e crianças para o seu navio. Boa sorte, capitão!";
			link.l1 = "Obrigado, senhor. Não vamos perder tempo!";
			link.l1.go = "Regata_Hovernor_4";
		break;
		
		case "Regata_Hovernor_wait":
			dialog.text = "Depressa, capitão. O tempo está acabando.";
			link.l1 = "Já estou navegando!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Hovernor_wait";
		break;
		
		case "Regata_Hovernor_exit":
			dialog.text = "Isto é inacreditável. Você nem vai tentar? Bem, esse é o seu direito. Não posso exigir nada de você. Se fosse um capitão qualquer, eu tomaria seu navio por causa de cem mulheres, mas você está participando da regata, e por isso está sob a proteção do governador-geral das colônias inglesas\nEu esperava que sua consciência falasse mais alto, mas me enganei. Vá, e que Deus tenha piedade da sua alma!";
			link.l1 = "Até logo, senhor.";
			link.l1.go = "Hovernor_exit";
		break;
		
		case "Hovernor_exit":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e)-36;//пятый противник выиграл 36 часов
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
			//вертаем губера в норму
			npchar.Dialog.Filename = "Common_Mayor.c";
			npchar.dialog.currentnode = "First time";
			//удаляем лейтенанта
			sld = characterFromId("SiegeOfficer");
			sld.lifeday = 0;
			//открываем ворота и выход в море
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			//остров в норму
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			for (i=1; i <=9; i++)//девок счистим
			{
				sld = characterFromId("RegataBridgWom_"+i);
				sld.lifeday = 0; // patch-7
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Regata", "38");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_Hovernor_4":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			NextDiag.CurrentNode = "Regata_Hovernor_wait";
			sld = characterFromId("SiegeOfficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
			pchar.quest.Regata_evacuation.win_condition.l1 = "location";
			pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
			AddQuestRecord("Regata", "36");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_BridgWom":
			dialog.text = "Os espanhóis estão atrás de nós! Deus, nos ajude!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_BridgWom";
		break;
		
		case "Regata_BridgWom_1":
			dialog.text = "O tenente Mahony está morto... isso só pode ser um pesadelo. Ele era um oficial corajoso. Capitão, por favor, pode nos levar até uma caverna? Só nos leve até lá e nós cuidaremos do resto.";
			link.l1 = "Claro. Me siga!";
			link.l1.go = "Regata_BridgWom_2";
		break;
		
		case "Regata_BridgWom_2":
			DialogExit();
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_BridgWom_3":
			dialog.text = "Aqui estamos... obrigado, capitão! Você acabou de nos salvar! Estive pensando em como te recompensar... existe uma maneira de aumentar suas chances na regata.";
			link.l1 = "Continue.";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_skiper":
			pchar.questTemp.Regata.Name = GetFullName(npchar);
			dialog.text = "Are you heading to Port Royal? The shortest route lies through Curaçao. Return to Bridgetown. Find a man named Woodrow Dougherty; he is an old sailor and an experienced navigator. He knows the area between Barbados and Jamaica perfectly, and he'd be a great help to you\nThis will save you a lot of precious time, which you so desperately need to win. Find the man in the local church and tell him that "+GetFullName(npchar)+" - has sent you, he won't turn you away. Take him to Port Royal, he was planning to sail there anyway.";
			link.l1 = "Muito bem! Um bom navegador vai me ser útil. Adeus.";
			link.l1.go = "Regata_skiper_1";
		break;
		
		case "Regata_skiper_1":
			dialog.text = "Até logo, capitão! Boa sorte!";
			link.l1 = "Talvez, a gente se encontre de novo...";
			link.l1.go = "Regata_skiper_2";
		break;
		
		case "Regata_skiper_2":
			DialogExit();
			AddQuestRecord("Regata", "37");
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			LAi_SetStayType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0; // patch-8
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0; // patch-8
			}
			//вертаем губера в норму
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			//открываем ворота и выход в море
			LocatorReloadEnterDisable("Shore4", "boat", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
			bQuestDisableMapEnter = false;
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			RegataSiegeSkiper();//поставим Вудро в церковь
		break;
		
		case "Regata_SiegeSkiper":
			dialog.text = "Bom dia. Gostaria de alguma coisa?";
			link.l1 = "Seu nome é Woodrow Dougherty, estou certo?";
			link.l1.go = "Regata_SiegeSkiper_1";
		break;
		
		case "Regata_SiegeSkiper_1":
			dialog.text = "Você tem razão. Em que posso ajudar?";
			link.l1 = "Eu sei que você é um navegador experiente e conhece bem as águas entre Barbados e Curaçao. Também sei que você quer chegar a Port Royal. Eu sou um dos participantes da regata e falta apenas uma última parada – Port Royal. Quero te convidar para se juntar à minha tripulação como navegador nessa viagem final.";
			link.l1.go = "Regata_SiegeSkiper_2";
		break;
		
		case "Regata_SiegeSkiper_2":
			dialog.text = "Interessante... E por que você acha que eu me juntaria à sua tripulação?";
			link.l1 = "Bem, porque ouvi falar de você por "+pchar.questTemp.Regata.Name+" com todas as garantias de que você não vai recusar. E por causa da minha ajuda a Bridgetown neste momento crítico...";
			link.l1.go = "Regata_SiegeSkiper_3";
		break;
		
		case "Regata_SiegeSkiper_3"://а тут - как уж свезет
			if(hrand(2) != 2)
			{
				dialog.text = "De "+pchar.questTemp.Regata.Name+"? Entendi agora, claro. Certo, Capitão, vou te ajudar a navegar pelo caminho mais curto até Port Royal. Vai zarpar agora?";
				link.l1 = "Sim.";
				link.l1.go = "Regata_SiegeSkiper_4";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.Regata.Name+"? Entendo. Mas, capitão, não posso abandonar minha cidade em tempos tão perigosos. Você deve me compreender como soldado que nos prestou ajuda sem interesse\nNão quero que as pessoas cochichem pelas minhas costas dizendo que o velho Woodrow fugiu diante da batalha final contra os espanhóis. Vou ficar. Não guarde rancor, capitão.";
				link.l1 = "E essa é sua palavra final? Mas eu ajudei sua colônia...";
				link.l1.go = "Regata_SiegeSkiper_6";
			}
		break;
		
		case "Regata_SiegeSkiper_4":
			dialog.text = "Então não vamos perder tempo. Só deixe-me arrumar minhas coisas e estarei à sua disposição.";
			link.l1 = "Meus marinheiros vão estar te esperando no cais e vão te levar até o 'Santa Catarina'. Obrigado, Woodrow!";
			link.l1.go = "SiegeSkiper_hire";
		break;
		
		case "Regata_SiegeSkiper_6":
			dialog.text = "Capitão, uma regata é um esporte, mas o cerco espanhol à minha casa é uma questão de vida ou morte. Eu não vou a lugar nenhum com você. E vou repetir, você precisa me entender – honra e dever ainda significam algo neste mundo. Esta é minha palavra final e não vou mudá-la. No entanto, posso lhe dar um conselho sobre como chegar lá rapidamente pela rota mais segura: navegue para noroeste em direção à Dominica, e de lá siga para Martinica ou Guadalupe, conforme você e o vento decidirem. Depois, siga direto para Port Royal, ou você pode passar por Curaçao – o que eu não recomendaria – mas se você estiver em bons termos com os holandeses, então vá em frente.";
			link.l1 = "Bem, obrigado... mas estou decepcionado. Adeus, Woodrow.";
			link.l1.go = "SiegeSkiper_exit";
		break;
		
		case "SiegeSkiper_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
		break;
		
		case "SiegeSkiper_hire":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = 25;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			//пересчитываем время пятого перехода
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp))+18+(rand(18));//выигрыш до 1.5 суток
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
			SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false);//чтобы не присвоил офицера
			DialogExit();
		break;
		
		case "Regata_Finish":
		iTest = FindColony("Portroyal"); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//снимаем запреты
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Você quebrou as regras da regata na última etapa. Seu resultado foi desclassificado. Não tenho mais nada a dizer a você, capitão.";
				link.l1 = "Ah... que droga! Bem, não tem mais jeito então, você foi atento demais. Adeus!";
				link.l1.go = "exit";
				npchar.lifeday = 1;
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				n=1;
				for (i=1; i <=5; i++)
				{
					if (i==1) sTemp = "a";
					if (i==2) sTemp = "b";
					if (i==3) sTemp = "c";
					if (i==4) sTemp = "d";
					if (i==5) sTemp = "e";
					if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
					pchar.questTemp.Regata.Result = n;//место в регате
				}
				if (n==1)
				{
					dialog.text = "Capitão "+GetFullName(pchar)+", meus parabéns! Levou "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" horas para você terminar a regata e você deixou todos os seus adversários muito para trás. Isso é um resultado incrível!";
					link.l1 = "Muito obrigado pelas suas palavras gentis, senhor!";
					link.l1.go = "First_result";
				}
				else
				{
					if (n==6)
					{
						dialog.text = "Capitão, infelizmente, o seu resultado é o pior, você gastou "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" horas. Não fique triste, você enfrentou adversários realmente difíceis.";
						link.l1 = "Não estou triste, senhor. Fico feliz por ter participado da regata e testado minhas habilidades.";
						link.l1.go = "Other_result";
						AddQuestRecord("Regata", "44");
						CloseQuestHeader("Regata");
					}
					else
					{
          				dialog.text = "Capitão, você está em "+n+"º lugar. Parabéns pelo seu resultado, você mostrou um tempo digno - "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" horas. Parabéns, apesar da sua derrota!";
						link.l1 = "Está tudo certo, senhor. Fico feliz por ter mostrado um bom resultado nessa competição difícil.";
						link.l1.go = "Other_result";
						if (n==2) AddQuestRecord("Regata", "40");
						if (n==3) AddQuestRecord("Regata", "41");
						if (n==4) AddQuestRecord("Regata", "42");
						if (n==5) AddQuestRecord("Regata", "43");
						CloseQuestHeader("Regata");
					}
				}
			}
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
			sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
			CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
			RemovePassenger(Pchar, sld);
			DeleteAttribute(sld, "Payment");
			DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
			log_info("Woodrow Dougherty has landed");
			pchar.quest.SiegeSkiperOver.over = "yes"; //снять таймер
		}
		else
		{
			dialog.text = "Senhor, me diga uma coisa – onde está seu navio? Não estou vendo ele...";
			link.l1 = "Me desculpe, senhor. Vou levá-la ao porto imediatamente.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Finish";
		}
		break;
		
		case "First_result":
			if (CheckAttribute(pchar, "questTemp.Regata.Rate")) sTemp = "Come and see me in my office. I will give you your prize for your stake.";
			else sTemp = "And if you had made a stake on your victory as I offered you to, you would have gotten an extra prize too.";
			dialog.text = "Visite o governador-geral amanhã e ele lhe dará seus 250.000 pesos e presentes valiosos. "+sTemp+" Não saia da cidade, segundo a tradição, os prêmios serão entregues ao tesouro da cidade se o vencedor não os reivindicar em uma semana.";
			link.l1 = "Entendi, senhor. Vou visitá-lo amanhã!";
			link.l1.go = "First_result_1";
		break;
		
		case "First_result_1":
			DialogExit();
			//npchar.lifeday = 7;
			Achievment_Set("ach_09");
			npchar.dialog.currentnode = "Other_result_repeat";
			pchar.questTemp.Regata.Win = "true";
			pchar.quest.Regata_Final.win_condition.l1 = "Timer";
			pchar.quest.Regata_Final.win_condition.l1.date.hour  = 6.0;
			pchar.quest.Regata_Final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Regata_Final.function = "RegataFinal";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false);//таймер не снимаем - через 8 дней подчистится все автоматически
			// слухи
			AddSimpleRumour("Ah, you are the legendary captain, the winner of the regatta! It's such a pleasure to see you in flesh!", ENGLAND, 60, 10);
			AddSimpleRumour("Ha, look at this, a master of wind and waves, the winner of the regatta! You have my respect...", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain who is capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Ah, so you are the legendary captain, the winner of the regatta! Pleasure to see you!", FRANCE, 60, 10);
			AddSimpleRumour("Ha, aren't you the master of wind and waves, the winner of the regatta! You have my respects...", FRANCE, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", FRANCE, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", FRANCE, 60, 10);
			// экспа
			AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 3);
			AddQuestRecord("Regata", "39");
			CloseQuestHeader("Regata");
		break;
		
		case "Other_result":
			dialog.text = "É bom ouvir uma resposta honrada. Boa sorte, Capitão!";
			link.l1 = "Até logo, senhor.";
			link.l1.go = "Other_result_1";
		break;
		
		case "Other_result_1":
			DialogExit();
			npchar.dialog.currentnode = "Other_result_repeat";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
			// экспа
			AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Other_result_repeat":
			dialog.text = "Quer mais alguma coisa, capitão?";
			link.l1 = "Não... não é nada.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Give_advantage":
			dialog.text = "Ah, aí está você, senhor "+GetFullName(pchar)+". Que bom te ver. Veio buscar seu prêmio? Está pronto para você.";
			link.l1 = "Que bom ouvir isso! Qual é o valor do meu prêmio extra?";
			link.l1.go = "Give_advantage_1";
		break;
		
		case "Give_advantage_1":
			dialog.text = "Levando tudo em conta, seu prêmio final é "+FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage))+". Por favor, fique com isso. Parabéns!";
			link.l1 = "Obrigado!";
			link.l1.go = "Give_advantage_2";
		break;
		
		case "Give_advantage_2":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
			dialog.text = "Sim, sua popularidade entre os cidadãos de Port Royal cresceu. Acho que você já percebeu isso... mas, infelizmente, a memória do povo é curta. Então aproveite a glória enquanto ela ainda brilha tão intensamente!";
			link.l1 = "Está falando das melhores coisas, senhor... Bem, vamos ver como é se banhar em glória. Adeus! Foi um prazer.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Regata_CitMan_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Parabéns pela vitória, capitão! Um resultado excelente!";
						link.l1 = "Obrigado!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Don't be sad, captain. Winning the regatta is no easy feat; even taking part in it is a privilege!";
						link.l1 = "Não se preocupe comigo. Estou satisfeito com meus resultados.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Que bom ver você, capitão! Você deve se registrar falando com o Sir Stevenson.";
					link.l1 = "Entendi. Estou a caminho dele!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, capitão, como você pôde falhar assim, logo na última etapa!";
				link.l1 = "Sim, que estupidez a minha...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitMan_1";
		break;
		
		case "Regata_CitWom_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Parabéns pela vitória, capitão! Um resultado excelente!";
						link.l1 = "Obrigado!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Don't be sad, captain. Winning the regatta is no easy feat; even taking part is a privilege!";
						link.l1 = "Não se preocupe comigo. Estou satisfeito com o meu resultado.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Que bom ver você, capitão! Você deve se registrar falando com Sir Stevenson.";
					link.l1 = "Entendi. Estou a caminho!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, capitão, por que você falhou assim, logo na última etapa!";
				link.l1 = "Sim, isso foi tão estúpido da minha parte...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitWom_1";
		break;
		
		case "Regata_CitHorse_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Parabéns pela vitória, capitão! Um resultado excelente!";
						link.l1 = "Obrigado!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Don't be sad, captain. It's not easy to win the regatta; even taking part is a privilege!";
						link.l1 = "Não se preocupe comigo. Estou satisfeito com o meu resultado.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Que bom ver você, capitão! Você deve se registrar falando com Sir Stevenson.";
					link.l1 = "Entendi. Estou a caminho!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, capitão, como você pôde falhar assim, logo na última etapa!";
				link.l1 = "Sim, que tolice a minha...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitHorse_1";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void CreateRegataAdversaries()
{
	string sTemp;
	for (int i=0; i<=4; i++)
	{
	if (i==0) sTemp = "a";
	if (i==1) sTemp = "b";
	if (i==2) sTemp = "c";
	if (i==3) sTemp = "d";
	if (i==4) sTemp = "e";
	pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
	pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
	pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4+frand(0.9);
	log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
	}
}
