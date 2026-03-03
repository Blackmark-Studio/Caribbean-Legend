// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <-- */
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = RandPhraseSimple("Um espião! Entregue sua arma e venha comigo!","Um agente inimigo! Peguem "+GetSexPhrase("ele","ela")+"!");
				link.l1 = RandPhraseSimple("Cale a boca, covarde!","Vai se ferrar!");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("Quem é você e o que está fazendo aqui?","Fique parado! Quem é você? Por que está tentando entrar no forte?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Oficial, eu tenho "+GetRusNameNationLicence(sti(npchar.nation))+", então estou aqui de forma legal. Aqui, por favor, dê uma olhada...";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Pirata no forte?! Peguem-no"+GetSexPhrase("ele","ela")+"!","Esse é um pirata, bisbilhotando nosso forte! Para a cadeia!!!");
							link.l1 = RandPhraseSimple("Sim, eu sou um pirata, e daí?","Hehe, me pega se conseguir...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Você não está vendo a bandeira de "+NationNameGenitive(sti(pchar.nation))+" no mastro do meu navio?!";
						}
						else //если причалил не в городе
						{
							link.l1 = "Ancorei perto de "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" sob a bandeira de"+NationNameGenitive(sti(pchar.nation))+"! Precisa de mais alguma coisa?";
						}
						// belamour legendary edition вызываюий доверие даёт возможность обмануть стражу
						if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
						{
							Notification_Perk(true, "Trustworthy");
							link.l1.go = "NotPegYou";
						}
						else
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
							{
								notification("Skill Check Failed", SKILL_SNEAK);
								link.l1.go = "PegYou";
							}
							else
							{
								link.l1.go = "NotPegYou";
							}
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Oh, capitão, tivemos momentos tão incríveis com você no mar! Tantos navios afundamos juntos sob seu comando! E aqui...";
									link.l1 = "E aqui, meu amigo, você pode admirar damas encantadoras que não vai encontrar no mar.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Capitão, o que fizemos para merecer isso?! Nós não somos ratos de terra, somos?";
									link.l1 = "Silêncio, marinheiro! Seu posto é muito importante e honrado, então pare de reclamar.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "O que está acontecendo no mar, capitão? Será que vamos vê-lo de novo?";
									link.l1 = "Mas é claro, marinheiro! Assim que estiver livre do serviço, pode ir até o cais e aproveitar o mar o quanto quiser.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Quero reclamar, capitão: todos nós sentimos falta do mar. Estamos completamente cansados desse serviço em terra!";
									link.l1 = "Cansei dessa choradeira! Aqui também tem rum de sobra! Sirva onde o capitão mandou, ou alguém vai acabar enforcado para servir de exemplo aos outros.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Vou te contar em confiança, capitão, o novo governador é um corrupto e ladrão de cofres públicos. Mas isso realmente não é da minha conta...";
									link.l1 = "Exatamente, corsário. Seu trabalho é ficar no seu posto e manter a ordem. E enforcar o governador no mastro é comigo. Bom trabalho!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Obrigado por não se esquecer da gente, capitão! A gente te seguiria até o fim do mundo!";
									link.l1 = "Eu conheço o tipo de vocês, malandros! No fundo, só se importam com ouro. Vai ter uma festa na taverna hoje à noite, as bebidas são por minha conta. Não esqueçam de aparecer.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Hein, capitão! Só pensa bem, será que um corsário pode mesmo ser guardião da ordem?! Faz tanto tempo desde a nossa última missão de verdade!";
									link.l1 = "Sem tempo para descansar, corsário! As armadas inimigas estão patrulhando as águas perto das nossas ilhas, e precisamos estar prontos para um banho de sangue a qualquer momento.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Capitão, ouvi dizer que a Coroa enviou mais um esquadrão para cá?";
									link.l1 = "Claro, corsário. Enquanto vivermos, não teremos paz. E até no Inferno, vamos lutar contra os demônios!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Caramba! Ontem aquele álcool estava forte demais, capitão! Pena que você não estava lá.";
									link.l1 = "Não é nada demais, eu vou compensar. E não tenho inveja de vocês, pessoal.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Vou te contar em confiança, capitão, já que você sempre nos tratou bem, ontem a gente se divertiu com uma moça realmente encantadora...";
									link.l1 = "Heh, corsário, uma forca é exatamente o que você merece!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Capitão! Por favor, me livre desse maldito dever! Eu simplesmente não aguento mais fingir que sou o guardião da ordem.";
									link.l1 = "Vigiar o navio à noite também não é fácil. Amigo, dever é dever, seja onde for.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("Temos um assunto importante!","Tenho assuntos a tratar com você.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
					}
					
					//Jason --> мини-квест Дефицитный товар
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
					{// Addon 2016-1 Jason пиратская линейка
						string wineCity = "FortFrance";
						if(SandboxMode)
						{
							if(CheckAttribute(pchar,"HeroParam.ToCityId"))
							{
								wineCity = pchar.HeroParam.ToCityId;	
							}
						}
						if(GetCityNameByIsland(LoadedLocation.islandId) ==  wineCity && npchar.location.locator == "protector1")
						{
							dialog.text = "Ei, camarada! Pode me fazer um favorzinho?";
							link.l1 = "Depende do que precisa ser feito.";
							link.l1.go = "Wine_soldier";
							link.l2 = "Não tenho tempo para isso.";
							link.l2.go = "exit";
							pchar.questTemp.Wine = "true";
							DelLandQuestMark(npchar);
							break;
						}
						if(StartHeroType == 2)
						{
							if(LoadedLocation.id == "Santiago_fort")
							{
								dialog.text = "Ei, camarada! Pode me fazer um favorzinho?";
								link.l1 = "Depende do que precisa ser feito.";
								link.l1.go = "Wine_soldier";
								link.l2 = "Não tenho tempo para isso.";
								link.l2.go = "exit";
								pchar.questTemp.Wine = "true";
								DelLandQuestMark(npchar);
								break;
							}
						}
					}
					// <-- мини-квест Дефицитный товар
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Sua Excelência, Governador-Geral! Em que posso servi-lo?";
							link.l1 = "Não preciso de nada, obrigado.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "É uma grande honra para mim, Sr. Governador Geral! Como posso ajudar?";
								link.l1 = "Cumpra seu serviço com dedicação - não exijo mais nada de você.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Que prazer vê-lo, Vossa Excelência! Em que um humilde soldado pode servir ao governador-geral das nossas colônias?";
								link.l1 = "Pessoalmente, não preciso de nada de você. Continue servindo.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Вице-адмирал на службе нации узнается без мундира
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Vice-Almirante, Vossa Excelência! Permita-me relatar: durante minha vigia...";
							link.l1 = "Calma, soldado, não preciso do seu relatório. Apresente-se ao seu superior.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Que bom ver você, Vice-Almirante! Posso ajudar em alguma coisa?";
								link.l1 = "Não, eu só estava testando o quanto você está atento. Fico feliz que tenha me reconhecido.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Vice-Almirante, é uma honra para mim! Em que posso ajudar?";
								link.l1 = "Servir "+NationNameGenitive(sti(npchar.nation))+", soldado! É a melhor coisa que você pode fazer.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Офицер с патентом
					if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Saudações, capitão! Se tiver alguma instrução para mim, peço desculpas: embora eu esteja a serviço de "+NationNameGenitive(sti(npchar.nation))+", eu só respondo ao comandante e ao governador."; 
							link.l1 = "Meus oficiais e a tripulação obedecem às minhas ordens. Cumpra seu dever, soldado.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Capitão, posso servir a bordo do seu navio? O mesmo serviço por "+NationNameGenitive(sti(npchar.nation))+", mas eu prefiro o mar."; 
								link.l1 = "Você é necessário onde foi designado, então cumpra seu dever com honra. Feche os olhos por um instante, e eles o levarão para o mar.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Ah, você está com sorte: é capitão de um navio a serviço de "+NationNameGenitive(sti(npchar.nation))+"... E eu fico preso aqui o dia todo."; 
								link.l1 = "Você acha que eu simplesmente cheguei ao Caribe e virei capitão uma semana depois? Isso aqui são anos de trabalho duro...";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Não está vendo? Estou de serviço. Pare de me incomodar.";
							link.l1 = "Tá bom, tá bom...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Você vai me contar sobre alguma atividade suspeita?";
							link.l1 = "Não, nenhuma, aliás, eu sou capitão. Vejo que você já não está mais ouvindo? Adeus.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Este é um local militar, então não faça muito barulho aqui.";
							link.l1 = "Certo, vou lembrar disso.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Tempo tão bom, e eu aqui parado. Na cidade pelo menos tem umas moças, mas aqui? Só rato pra todo lado.";
							link.l1 = ""+GetSexPhrase("Eu entendo, mas não posso fazer nada para ajudar – afinal, é seu dever.","Ei! O que há de errado comigo? Eu não sou uma mulher?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Se gosta de conversar, procure outra pessoa. Preciso manter a ordem aqui e não tenho tempo para papo furado.";
							link.l1 = "Ah, não, só estou vendo se você ainda está vivo. Você estava parado feito uma estátua.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Você provavelmente acha que servir na guarnição é moleza? De jeito nenhum! É um trabalho duro e importante. Eu me lembro de uma vez... ";
							link.l1 = "Você me conta essa história outra hora. Agora estou com um pouco de pressa.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Cuidado aqui, você está em um forte! Fique quieto como um rato!";
							link.l1 = "Como quiser, soldado.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Ei! Você tem um pouco de água, por acaso? Estou morrendo de sede.";
							link.l1 = "Não, camarada, mantenha a calma...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "Como é monótona a vida na guarnição, só tem caipira como você por aqui! Agora, a guarnição da cidade com certeza se diverte bem mais...";
							link.l1 = "E você chama isso de 'estar de serviço'? Desse jeito, com certeza vai deixar um espião passar por você!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("Você parece ser um sujeito forte, não é? Gostaria de se alistar para servir na guarnição do forte? Temos alojamentos espaçosos, duas refeições por dia e bebida de graça.","Oh, senhorita, você não faz ideia de como é agradável encontrar uma moça tão encantadora neste fim de mundo!")+"";
							link.l1 = ""+GetSexPhrase("Isso é realmente tentador, mas ainda assim preciso recusar. Toda essa rotina de quartel não é pra mim.","Obrigada pelo elogio, soldado.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Esse maldito calor... Eu daria de bom grado metade da minha vida pra voltar pra Europa.";
							link.l1 = "Sim, posso ver que sua saúde não está adaptada ao clima daqui.";
							link.l1.go = "exit";
						break;
					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Hum... Entendi. Aqui está o que "+GetSexPhrase("хотел","хотела")+" perguntar... ";
					link.l3.go = "quests";//(перессылка в файл города) */
				}
			}
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_soldier":
			dialog.text = "Veja, eu estou morrendo de vontade de tomar um vinho... Mas não quero aquela bebida local feita de fruta podre, que vendem por dois pesos o barril – quero uma garrafa de vinho europeu de verdade. Você pode conseguir com os mercadores na cidade. É bem caro, mas eu pago tudo e ainda te dou trezentos pesos a mais. Então, vai trazer pra mim?";
			link.l1 = "E por que você mesmo não pode pegar isso? Não vai precisar pagar a mais, é só esperar ser dispensado do seu posto e ir atrás. Qual é o truque?";
			link.l1.go = "Wine_soldier_1";
		break;
		
		case "Wine_soldier_1":
			dialog.text = "Não tem truque. Eu só não posso sair do forte pra ir até a cidade enquanto não me liberarem, e isso não vai acontecer tão cedo. Além disso, nosso comandante proibiu terminantemente qualquer bebida alcoólica no forte, maldito seja! Então, vai ajudar um soldado?";
			link.l1 = "Por que não? Eu trago esse vinho pra você, estou com um tempo livre mesmo.";
			link.l1.go = "Wine_soldier_2";
			link.l2 = "Desculpe, amigo, mas não posso fazer isso. Procure outra pessoa para te ajudar.";
			link.l2.go = "exit";
		break;
		
		case "Wine_soldier_2":
			dialog.text = "Ótimo! Muito obrigado! Hoje estou de vigia, então venha amanhã. Você vai me encontrar no alto do forte, onde pode me passar a garrafa sem que ninguém perceba...";
			link.l1 = "Certo. Espere por mim, amanhã eu vou te ver.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.id = npchar.ID;
			pchar.questTemp.Wine.SName = GetFullName(npchar);
			pchar.questTemp.Wine.bottle = "true";
			npchar.lifeday = 5;
			SetFunctionTimerCondition("Wine_Exchange", 0, 0, 1, false);
			pchar.questTemp.Wine.City = GetCityNameByIsland(LoadedLocation.islandId);
			if(StartHeroType == 2) pchar.questTemp.Wine.City = "Santiago";
			Log_TestInfo(pchar.questTemp.Wine.City);
			SaveCurrentQuestDateParam("questTemp.Wine_bottle");
			AddQuestRecord("Wine", "0");
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
		// <-- мини-квест Дефицитный товар
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Me parece que isso é algum tipo de trapaça. Vamos falar com o comandante, "+GetSexPhrase("companheiro","querida")+", e descobrir tudo isso...","Hmm... Algo me diz que você não é quem diz ser... Entregue sua arma "+GetAddress_Form(npchar)+", e me siga para uma investigação mais detalhada!");
			link.l1 = RandPhraseSimple("Vai se ferrar!","Quando dois domingos caem na mesma semana...");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Ah, entendi... Está tudo certo, pode ir, "+GetAddress_Form(pchar)+".","Devo ter ficado um pouco cansado de ficar de vigia... Parece que está tudo bem, "+GetAddress_Form(pchar)+", me desculpe.");
			link.l1 = "Sem problema!";
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Pense só nisso! Que insolência! Aparecer aqui fingindo ser um mercador! Seu rosto está em todos os quartéis, seu desgraçado! Desta vez você não vai escapar! Agarrem ele!";
				link.l1 = RandPhraseSimple("Arrgh!..","Bem, você pediu por isso...");
				link.l1.go = "fight";	
				break;
			}
			if (findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе
			{
				dialog.text = "Veio negociar aqui? Posso saber como? Onde está seu navio? Sabe, tudo isso parece muito suspeito, e sou obrigado a detê-lo até esclarecermos tudo. Entregue sua arma e venha comigo!";
				link.l1 = RandPhraseSimple("Vai se ferrar!","Quando dois domingos caírem na mesma semana...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Sua licença deve ser revogada, pois está expirada e, portanto, inválida. Entregue sua arma e me acompanhe para uma investigação mais detalhada!";
				link.l1 = RandPhraseSimple("Vai se ferrar!","Quando dois domingos caírem na mesma semana...");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hum... Parece que está tudo em ordem. Mas preciso avisar que sua licença vence hoje. Vou deixar você passar desta vez, mas ainda assim vai precisar tirar uma nova licença.";
				link.l1 = "Obrigado, farei isso assim que possível.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Tudo parece em ordem. Mas preciso avisar que sua licença vai expirar em breve. Ela é válida apenas até "+FindRussianDaysString(iTemp)+". Então lembre-se disso, "+GetAddress_Form(npchar)+".";
				link.l1 = "Obrigado, vou providenciar um novo assim que possível.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Bem, está tudo certo. Sua licença está válida por "+FindRussianDaysString(iTemp)+". Pode passar.","Está tudo claro, "+GetAddress_Form(npchar)+". Você está livre para entrar e sair da cidade, sua licença é válida por  "+FindRussianDaysString(iTemp)+". Desculpe incomodar você.","Está tudo certo, "+GetAddress_Form(npchar)+", não vou mais te segurar aqui.");
				link.l1 = RandPhraseSimple("Excelente. Saudações.","Obrigado, oficial.");
				link.l1.go = "exit";
			}
		break;

		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
				dialog.text = "Captain, I ask you to put away your weapons; it is forbidden to draw them in our city.";
				link.l1 = LinkRandPhrase("Certo, eu vou guardar...","Já está feito.","Como quiser...");
				link.l1.go = "exit";
				link.l2 = LinkRandPhrase("Vai se ferrar!","Acho que vou usar isso!","Vou guardar quando chegar a hora certa.");
				link.l2.go = "fight";
				npchar.greeting = "soldier_common";
				NextDiag.TempNode = "First Time";
				break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("Por que diabos você está correndo por aí com a espada desembainhada? Guarde sua arma agora mesmo!","Estou ordenando que você embainhe sua arma imediatamente!","Ei, "+GetSexPhrase("companheiro","moça")+", pare de assustar o pessoal! Guarde sua arma.");
			link.l1 = LinkRandPhrase("Tudo bem.","Certo.","Como você quiser...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Vai se ferrar!","Não faz mal sonhar...","Quando dois domingos caem na mesma semana.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}
