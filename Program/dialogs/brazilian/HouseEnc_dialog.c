void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;
	
	int iTest;
	
	bool  ok; // лесник . спецпеременная.

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Soaram os alarmes na cidade. Pelo visto, chegou a minha hora de pegar em armas também...","Os guardas da cidade não estão te perseguindo, por acaso? ","Você não vai encontrar abrigo aqui, mas pode muito bem acabar com alguns centímetros de aço frio entre as costelas!"),LinkRandPhrase("O que você precisa?"+GetSexPhrase("canalha","canalha")+"?! Os guardas da cidade já sentiram seu cheiro, você não vai longe, "+GetSexPhrase("pirata imundo","sua pirata safada")+"!","Assassino imundo! Guardas!!!","Eu não tenho medo de você, "+GetSexPhrase("desgraçado","vadia")+"! Em breve você será enforcado em nosso forte, não vai chegar muito longe..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Vejo que você está cansado de viver...","Pelo visto, não há vida tranquila para os cidadãos de "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Vai pro inferno!","Heh, esses serão os últimos segundos da sua vida..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Eu já te avisei. Agora você decide se quer se meter em encrenca.";
					link.l1 = "Heh!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "O que você quer na minha casa, canalha?! Você tem dez segundos pra sair daqui!";
					link.l1 = LinkRandPhrase("Heh, parece que aqui também me conhecem!","A minha fama acabou de chegar antes de mim...","Hum, entendi.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Fico feliz em receber você na minha casa. Veio tratar de algum assunto comigo?","O que posso fazer por você?","Hmm... O que posso fazer por você?","Me desculpe, mas se não tem nenhum assunto comigo, por favor, não me incomode...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Não, só estou dando uma olhada, conhecendo gente nova...","Não, nada em especial...","Nada...","Tudo bem, como quiser.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Me desculpe, mas a noite não é o melhor momento para visitas, então preciso pedir que você saia da minha casa agora mesmo!","Já te disse, está tarde. Por favor, vá embora.","Não quero parecer grosseiro, mas insisto que você saia da minha casa imediatamente!","Maldição, o que está acontecendo?! Guardas! Ladrões!","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Certo, entendi...","Sim, só um momento...","Certo, só não se empolgue tanto.","Que ladrões?! Cala a boca!",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "Oh, permita-me apresentar - "+GetFullName(npchar)+". Estamos muito felizes em tê-lo como nosso hóspede. Nesta cidade, as leis da hospitalidade são respeitadas.";
			link.l1 = GetFullName(pchar)+", se não se importa...";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Você é "+GetSexPhrase("um ladrão, hein! Guardas, peguem ele","uma ladra, hein! Guardas, prendam ela")+"!!!","Não acredito nisso! Virei de costas por um segundo – e você já está mexendo nas minhas coisas! Pare, ladrão!!!","Guardas! Roubo! Parem o ladrão!!!");
			link.l1 = "Aaaah, diabo!!!";
			link.l1.go = "fight";
		break;
		// --------------------------------- баба ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Estou avisando, meu marido vai voltar logo! É melhor você sair da minha casa agora!","Eu duvido que você consiga escapar! E saiba que meu marido vai chegar em casa em breve!","Meu marido vai chegar em casa logo! Você precisa ir embora agora!"),LinkRandPhrase("Uma pena que meu marido não está em casa... Saia! Agora!!!","Assassino imundo, saia da minha casa agora mesmo! Guardas!",""+GetSexPhrase("Que canalha","Que nojeira")+"... Logo meu marido vai voltar, e ele vai ver de que cor é o seu sangue!"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Oh, seu marido... oooooh... estou até tremendo...","Heh... Sabe, moça, seu marido é só um homem... você não ia querer ele morto aos seus pés, ia?"),RandPhraseSimple("Cala a boca, vadia, antes que eu te corte...","Eu vou ficar aqui o tempo que eu quiser. E é melhor você ficar de boca fechada se sabe o que é bom pra você..."));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Eu já te avisei. Saia daqui ou vai se arrepender!";
					link.l1 = "Que mulher tola...";
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = "O que você está fazendo na minha casa, "+GetSexPhrase("canalha","canalha")+"?! Se você não sumir em dez segundos, vou chamar os guardas!";
					link.l1 = "Que mulher idiota...";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Fico feliz em ver você em nossa casa. Meu nome é "+GetFullName(npchar)+". O que posso fazer por você?","Você ainda está aqui?","Hum, com licença, mas você não acha que já está na hora de ir embora?","Eu pediria, por favor, que não abuse da nossa hospitalidade.","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(GetFullName(pchar)+" ao seu dispor. Vim aqui sem nenhum motivo especial, só para conhecer você.","Ainda aqui.","Bem, eu não sei...","Certo.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Meu Deus, por que você está invadindo minha casa a essa hora! Você realmente me assustou... Por favor, venha nos visitar amanhã!","Por favor, saia da nossa casa!"+GetSexPhrase("","Eu sou uma mulher casada!")+"","Estou pedindo que você deixe nossa casa pela última vez!","Mas o que está acontecendo aqui?!","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Não tenha medo, eu não vou te machucar.","Certo, só não fique tão agitado.","Estou indo embora.","E aí?",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "Sempre ficamos felizes em receber visitas. Só não fique aqui por muito tempo,"+GetSexPhrase(", já que sou uma mulher casada..."," já que tenho muito o que fazer...")+"";
			link.l1 = "Ah, sim, claro...";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = "Então é assim? Eu te recebi como meu convidado, e você está fuçando nos nossos baús?! Guardas!";
			link.l1 = "Cala a boca, sua vadia!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = "Eu pedi educadamente para você sair da nossa casa, mas você simplesmente não quis ouvir! Chega! Socorro! Guardas!";
			link.l1 = "Cale a boca, sua mulher tola! Você ficou louca?!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- завсклад ---------------------------------		
		case "SkladMan":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Soaram os alarmes na cidade. Pelo visto, chegou a minha hora de pegar em armas também...","Os guardas da cidade não estão atrás de você, por acaso? ","Você não vai encontrar abrigo aqui, mas pode muito bem acabar com alguns centímetros de aço frio entre as costelas!"),LinkRandPhrase("O que você precisa?"+GetSexPhrase("canalha","canalha")+"?! Os guardas da cidade já sentiram seu cheiro, você não vai longe, "+GetSexPhrase("pirata imundo","vadia")+"!","Assassino imundo! Guardas!!!","Eu não tenho medo de você, "+GetSexPhrase("desgraçado","vadia")+"Em breve você vai ser enforcado no nosso forte, não vai chegar muito longe..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Vejo que você está cansado de viver...","Pelo visto, não há vida tranquila para os cidadãos de "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Vá para o inferno!","Heh, esses vão ser os últimos segundos da sua vida..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
				dialog.text = NPCStringReactionRepeat("Bem-vindo! Meu nome é "+GetFullName(npchar)+". Aqui, quem manda sou eu, então nem pense em levar nada com você...","Comporte-se e lembre-se de que estou de olho em você.","Desde que você não mexa nos baús, pode ficar aqui. De qualquer forma, estou entediado sozinho...",RandPhraseSimple("Ai, estou tão entediado!","Maldição, o que eu faço? Ficar aqui é tão entediante!"),"block",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tá bom, não se preocupe.","Claro!","Entendi...","É, isso parece um problema.",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
		break;
		
		case "SkladMan1":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Soaram os alarmes na cidade. Pelo visto, chegou a minha hora de pegar em armas também...","Os guardas da cidade não estão te perseguindo, por acaso? ","Você não vai encontrar abrigo aqui, mas pode muito bem acabar com alguns centímetros de aço frio entre as costelas!"),LinkRandPhrase("O que você precisa?"+GetSexPhrase("canalha","canalha")+"?! Os guardas da cidade já sentiram seu cheiro, você não vai longe, "+GetSexPhrase("pirata imundo","vadia")+"!",""+GetSexPhrase("Imundo","Imundo")+" Assassino! Guardas!!!","Eu não tenho medo de você, "+GetSexPhrase("desgraçado","vadia")+" ! Logo você será enforcado em nosso forte, não vai chegar longe... "));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Vejo que você está cansado de viver...","Parece que não há vida tranquila para os cidadãos de "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Vá para o inferno!","Heh, esses serão os últimos segundos da sua vida..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			dialog.text = NPCStringReactionRepeat("Aqui, quem manda sou eu, então nem pense em levar nada com você...","Comporte-se e lembre-se de que estou de olho em você.","Desde que você não mexa nos baús, pode ficar aqui. Eu estou entediado sozinho, de qualquer forma...",RandPhraseSimple("Ai, estou tão entediado!","Droga, o que eu faço? Ficar aqui é tão entediante!"),"block",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Certo, não se preocupe.","Claro!","Entendi...","É, isso parece um problema.",npchar,Dialog.CurrentNode);	
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
			//открывание двери верфи по квесту промышленного шпионажа
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
			{
				link.l2 = "Escute, camarada, quero falar com você abertamente.";
				link.l2.go = "ShipyardsMap_1";
				pchar.questTemp.different.ShipyardsMap = "toResult";					
			}
			// ugeen --> склад товаров для ГГ				
			if(CheckAttribute(NPChar,"Storage"))
			{
				if(!CheckAttribute(NPChar, "Storage.Speak"))
				{
					dialog.text = "Tenho uma proposta tentadora para você. Talvez se interesse por ela.";
					link.l7 = "Sério? Tudo bem, estou ouvindo.";
					link.l7.go = "storage_rent";
				}
				else
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Leve-me ao armazém. Quero ver em que estado ele está.";
						link.l7.go = "storage_0";
						link.l8 = "Decidi desocupar o armazém. Não preciso mais dele.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "Você mencionou um armazém. Ele ainda está vazio?";
							link.l7.go = "storage_01";
						}						
					}
				}		
			// <-- ugeen
			}		
		break;
		
		//--------------------------------- Аренда склада ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = "Temos uma área adequada para servir de armazém. Gostaria de alugá-la por um preço justo? Imagine só, você teria seu próprio armazém para guardar cargas valiosas...";
			link.l1 = "Um armazém, você diz? Sim, é tentador, de fato... Mas ele é grande o bastante? E quanto vai cobrar pelo aluguel?";
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "É bem espaçoso, mesmo para um armazém portuário. Cabe, vejamos... 50.000 centenários de carga. Para "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+"  por mês eu posso guardar suas mercadorias em segurança. "+"Isso inclui guardar com meus homens, proteger contra infiltração de água e lutar contra os ratos. O que me diz? Ah, e discrição também, claro, isso nem precisa dizer.";
			link.l1 = "Pode deixar. Posso dar uma olhada?";	
			link.l1.go = "storage_rent2";
			link.l2 = "Isso é demais. E aposto que está alagado e infestado de ratos.";
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = "Claro, claro. Mas... vou precisar de um mês de pagamento adiantado. ";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Você é... realmente um comerciante e tanto, devo admitir. Aqui está seu dinheiro... Vou alugar este galpão.";
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 = "Você é... bem mercenário, devo dizer. Tudo bem, vou buscar o dinheiro.";
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = "Como quiser. Se mudar de ideia, é só me avisar. E lembre-se que um armazém tão bom assim dificilmente vai ficar vazio por muito tempo...";
			link.l1 = "Sem problema. Eu aviso se precisar.";
			link.l1.go = "exit";
		break;
		
		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "E quanto ao aluguel, você ainda me deve  "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Certo, vou pagar o aluguel agora.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Vou voltar mais tarde.";
					link.l1.go = "exit";
				}
			}		
			else
			{ // лесник . если забыл с собой корабль то никак.
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Pode ir em frente.";
				link.l1 = "Obrigado.";
				link.l1.go = "storage_2";
				}
				else
				{
                dialog.text = RandPhraseSimple("Capitão, onde está seu navio? Como pretende transportar a carga?","Não vejo seu navio atracado no porto. Como exatamente você pretende carregá-lo?");
                link.l1 = RandPhraseSimple("Oh... Eu tinha esquecido completamente disso!","Droga, é isso mesmo!");
			    link.l1.go = "exit";
				break;
                }			
			}
			link.l2 = "Não, mudei de ideia.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "Não, "+GetSexPhrase("senhor","senhora")+", ainda está vaga e esperando por você. Eu sabia que no fim das contas você não recusaria minha oferta.";
			link.l1 = "Muito bem. Eu vou alugar.";
			link.l1.go = "storage_1";
			link.l2 = "Não, só me veio à cabeça...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Como você deve se lembrar, preciso do pagamento de um mês adiantado.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Claro, eu me lembro. Aqui está.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Droga. Tá bom, eu vou buscar o dinheiro.";
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
			dialog.text = "Já vai embora? Que pena, aqui é realmente um lugar excelente com condições ótimas. Garanto que não vai encontrar um negócio assim em nenhum outro lugar do Caribe.";
			link.l1 = "Eu disse, estou desocupando. Ou você quer que eu pague pra guardar ar? Pode procurar outro inquilino.";
			link.l1.go = "storage_4";
			link.l2 = "Em nenhum lugar do Caribe, você diz? Tudo bem, vou ficar com ele por um tempo, então. Mas o aluguel, devo dizer, está um pouco alto demais.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "E quanto ao aluguel, você ainda me deve "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Certo.";
					link.l1.go = "storage_5";
				}
			}
			else
			{ // лесник . если нет корабля то и товар не забрать
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Recolha suas mercadorias, e eu vou fechar o armazém.";
				link.l1 = "Certo.";
				link.l1.go = "storage_6";
				}
				else
				{
                dialog.text = RandPhraseSimple("Capitão, onde está o seu navio? Como pretende transportar a carga?","Não vejo seu navio atracado no porto. Como exatamente você pretende carregá-lo?");
                link.l1 = RandPhraseSimple("Oh... Eu tinha esquecido completamente disso!","Droga, é isso mesmo!");
			    link.l1.go = "exit";
				break;
                }				
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

		//--------------------------------- Аренда склада ---------------------------------
		
		case "ShipyardsMap_1":
			dialog.text = "Heh! Tudo bem, vamos conversar.";
			link.l1 = "Preciso chegar ao estaleiro à noite, quando não houver ninguém por perto.";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "Olha só pra você! Ei, guardas, temos um ladrão aqui!!!";
				link.l1 = "Que ladrão? Eu só queria conversar!";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingL", 5);
				AddCharacterExpToSkill(pchar, "FencingS", 5);
				AddCharacterExpToSkill(pchar, "FencingH", 5);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
				dialog.text = "Caramba! Olha só pra você, "+GetSexPhrase("companheiro","moça")+". Vir até o armazém do estaleiro com um pedido desses!";
				link.l1 = "Eu preciso ir direto ao estaleiro. Não dou a mínima para o seu armazém.";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "Mas por que você precisa disso?";
			link.l1 = "Existe uma necessidade. E estou disposto a pagar por isso...";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "Hum, assim está melhor... Certo! Me passa "+FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000)+", e vou deixar a porta do estaleiro aberta no dia seguinte.";
			link.l1 = "Está caro demais. Vou ter que ficar sem isso, então...";
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "Certo, eu concordo. Pegue seu dinheiro e faça como combinamos.";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "Não se preocupe, vai ser feito.";
			link.l1 = "Espero que sim...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//снимаем close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//ставим таймер на возврат close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}
