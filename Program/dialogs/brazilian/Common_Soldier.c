// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int DeceptionChance  = 0;
	int DeceptionPenalty  = 0;
	if(CheckAttribute(pchar,"StealtDeceptionPenalty")) DeceptionPenalty = sti(pchar.StealtDeceptionPenalty);
	
	DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/110);
	if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	if (false) 
	{
		DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/310);
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
	{
		DeceptionChance = 100;
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(DeceptionChance > 90) DeceptionChance = 90;
	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
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
			if (false)
			{
				// заглушка на пирата
				if (false)
				{
    				dialog.text = RandPhraseSimple("Piratas na cidade?! Não acredito... Peguem "+GetSexPhrase("ele","ela")+"!!","É um pirata! Peguem "+GetSexPhrase("ele","ela")+"!!!");
					link.l1 = RandPhraseSimple("Eu sou um pirata, e daí?","Heh, pode tentar...");
					link.l1.go = "fight"; 
					break;
				}
				else
				{
					if (DeceptionChance > (10+rand(150)+rand(150)))
					{
						dialog.text = RandPhraseSimple("Quem é você e o que está fazendo aqui?","Pare aí mesmo! Quem é você, e com que direito está tentando entrar na cidade?");
						link.l2 = "Ancorei perto de "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" sob a bandeira de "+NationNameGenitive(sti(npchar.nation))+". O que você não entende? (Probabilidade de engano "+DeceptionChance+"%%)";
						link.l1.go = "NotPegYou";
					}
					else
					{
						dialog.text = RandPhraseSimple("Um espião! Entregue sua arma e venha comigo!","Um agente inimigo! Peguem "+GetSexPhrase("ele","ela")+"!");
						link.l1 = RandPhraseSimple("Cala a boca, maricas!","Vai se foder!");
						link.l1.go = "fight"; 
					}
				}
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (false)
				{
					// грамота Винсенто
					if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
					{
						dialog.text = RandPhraseSimple("Quem é você e o que está fazendo aqui?","Pare aí mesmo! Quem é você, e com que direito tenta entrar na cidade?");
						link.l1 = "Olhe este documento, soldado. Estou aqui com permissão do Inquisidor, Padre Vincenzo.";
						link.l1.go = "vincento"; 
						break;
					}
					if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
					{
						dialog.text = RandPhraseSimple("Quem é você e o que está fazendo aqui?","Pare aí mesmo! Quem é você, e com que direito está tentando entrar na cidade?");
						link.l1 = "Olhe este documento, soldado. Estou aqui com permissão do Inquisidor, Padre Vincento.";
						link.l1.go = "vincento"; 
						break;
					}
					if (PChar.location == "Maracaibo_Plantation")
					{
						dialog.text = LinkRandPhrase("Comporte-se e não incomode os escravizados.","Ande logo, siga em frente!","Ah, é você. Pode passar, já fomos avisados sobre você.");
						link.l1 = "...";
						link.l1.go = "exit";
						break;
					}
					dialog.text = RandPhraseSimple("Quem é você e o que está fazendo aqui?","Pare aí mesmo! Quem é você e com que direito está tentando entrar na cidade?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Oficial, eu tenho "+GetRusNameNationLicence(HOLLAND)+", então estou aqui legalmente. Aqui, por favor, dê uma olhada...";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = "Você não está vendo a bandeira de "+NationNameGenitive(sti(pchar.nation))+"no mastro do meu navio?! (Probabilidade de engano "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l2 = "Ancorei perto de "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" sob a bandeira de "+NationNameGenitive(sti(pchar.nation))+". O que você não entende? (Probabilidade de engano "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (false)
						{
    						dialog.text = RandPhraseSimple("Piratas na cidade?! Não acredito... Peguem ele!","É um pirata! Peguem ele!");
							link.l1 = RandPhraseSimple("Sim, eu sou um pirata - e daí?","Hehe, me pega se conseguir...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Você não está vendo a bandeira de "+NationNameGenitive(sti(pchar.nation))+" no meu navio?! (Probabilidade de engano "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l1 = "Ancorei perto de "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" sob a bandeira "+NationNameGenitive(sti(pchar.nation))+". O que você não entende? (Probabilidade de engano "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Oh, capitão, nós nos divertimos tanto com você no mar! Tantos navios afundamos juntos sob seu comando! E aqui...";
									link.l1 = "E aqui, meu amigo, você pode admirar belas damas que não se vê no mar.";
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
									link.l1 = "Estou cansado dessa choradeira! Aqui também tem rum de sobra! Sirva onde o capitão mandou, ou alguém vai acabar enforcado para servir de exemplo aos outros.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Vou te contar em confiança, capitão, o novo governador é um corrupto e ladrão. Mas isso realmente não é da minha conta...";
									link.l1 = "Exatamente, corsário. Seu trabalho é ficar no seu posto e manter a ordem. E enforcar o governador no mastro é comigo. Bom trabalho!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Obrigado por não se esquecer da gente, capitão! A gente te seguiria até o fim do mundo!";
									link.l1 = "Eu conheço o tipo de vocês, bandidos! Tudo o que realmente importa pra vocês é ouro. Vai ter uma festa na taverna hoje à noite, as bebidas são por minha conta. Não esqueçam de aparecer.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Hein, capitão! Já pensou, um corsário sendo guardião da ordem?! Faz tanto tempo que não pegamos um serviço de verdade!";
									link.l1 = "Sem tempo para descansar, corsário! As armadas inimigas estão patrulhando as águas perto das nossas ilhas, e precisamos estar prontos para um banho de sangue a qualquer momento.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Capitão, ouvi dizer que a Coroa mandou mais um esquadrão para cá?";
									link.l1 = "Claro, corsário. Enquanto estivermos vivos, não haverá paz para nós. E mesmo no Inferno, continuaremos lutando contra os demônios!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! Caramba, aquela bebida de ontem estava forte demais, capitão! Pena que você não estava lá.";
									link.l1 = "Não é nada demais, eu vou compensar. E não tenho inveja de vocês, pessoal.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Vou te contar em confiança, capitão, já que você sempre nos tratou bem. Ontem nos divertimos muito com uma moça realmente encantadora...";
									link.l1 = "Heh, corsário, uma forca é exatamente o que você merece!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Capitão! Por favor, me livre desse maldito dever! Eu simplesmente não aguento mais fingir que sou o guardião da ordem.";
									link.l1 = "Vigiar o navio à noite também não é fácil. Amigo, dever é dever, seja onde for, seja qual for.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("Tem algo importante!","Tenho assuntos a tratar com você.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
						else
						{ // пираты, не наши
							if (sti(pchar.GenQuest.Piratekill) > 20)
							{
								dialog.text = RandPhraseSimple("Alerta! Um lunático armado e fora de si está aqui!","Às armas, às armas! Tem um maluco aqui!");
								link.l1 = RandPhraseSimple("Hã? O quê?","Uh, por que você está fazendo isso?");
								link.l1.go = "pirate_fight";
							}
							else
							{
							    /* dialog.text = LinkRandPhrase(RandPhraseSimple("Tem algum assunto comigo, Capitão?","Só estou aqui a trabalho, se precisar de algo - é só pedir, não hesite."),RandPhraseSimple("Capitão, estou muito ocupado, então procure outra pessoa para conversar.","Há algum problema, Capitão? Se não tiver perguntas, posso me retirar?"),"Abra caminho, Capitão, estou com pressa.");
							link.l1 = LinkRandPhrase("Desculpa, camarada, eu "+GetSexPhrase("Me confundi","обозналась")+" ","Certo, trate dos seus assuntos.","Não, nada.");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("Tenho algumas perguntas para você.","Tenho negócios com você."),RandPhraseSimple("Vejo que está com pressa. Só uma pergunta e já te libero.","Я "+GetSexPhrase("хотел","хотела")+" perguntar algo."),"Seu assunto pode esperar. Tenho algo para te perguntar "+GetSexPhrase("хотел","хотела")+".");
							    link.l2.go = "quests";//(перессылка в файл города) */
								
								//Экку Korsar - что-то они больно вежливые для пиратов были...
								dialog.text = RandPhraseSimple("O que você quer? Vai andando.","Pare de bloquear o caminho, saia da frente.");
					            link.l1 = RandPhraseSimple("Sabe? Não grite!","Controle esse fogo. Não vou esfriar as coisas tão rápido!");
					            link.l1.go = "exit";
						    	/* link.l2 = LinkRandPhrase(RandPhraseSimple("Tenho algumas perguntas para você.","Tenho assuntos a tratar com você."),RandPhraseSimple("Vejo que você está com pressa. Só uma pergunta e você estará livre.","Я "+GetSexPhrase("хотел","хотела")+" perguntar algo."),"Seu assunto pode esperar. Tenho algo para te perguntar "+GetSexPhrase("хотел","хотела")+".");
							link.l2.go = "quests";//(перессылка в файл города) */
							}
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("Olhe só  "+GetSexPhrase("aquele canalha! Teve a ousadia de aparecer por aqui","olha só para aquela canalha! Ela teve a ousadia de aparecer")+" em "+XI_ConvertString("Colony"+npchar.city)+". Tomar "+GetSexPhrase("ele","ela")+"!!!","Ha, eu reconheço você, "+GetSexPhrase("canalha","canalha")+"! Capture "+GetSexPhrase("ele","ela")+"!!!");
							link.l1 = RandPhraseSimple("Argh!..","Bem, você pediu por isso...");
							link.l1.go = "fight";
							break;						
						}
					}

					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)	
						{
							dialog.text = "Oh, olha só quem apareceu! Lady "+pchar.GenQuest.EncGirl.name+" ela mesma nos honrou com sua presença! Fico curioso para saber como teve coragem? Estávamos te procurando! Por favor, siga para o calabouço – sua cela já está pronta e esperando por você. ";
							link.l1 = "Que absurdo é esse que você está falando!? Minha tripulação e eu "+GetSexPhrase("cavalheiro","companheiro")+" estávamos passeando na selva, colhendo flores. Me deixe em paz! Onde estão os modos desses mandões?! Assim que veem uma moça bonita, já começam a importunar! "+GetSexPhrase("Meu querido, por favor, diga àqueles idiotas para sumirem e deixarem uma mulher honesta em paz!","Querido, por favor diga àqueles cabeças-duras...")+"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)	
						{
							dialog.text = "Ah, aí está você, linda! Seu pai mobilizou toda a guarnição pra te encontrar e levar de volta pra casa.";
							link.l1 = "Saia daqui! Eu sei para onde estou indo e não preciso da sua ajuda! Capitão, diga para eles tirarem as mãos de mim.";
							link.l1.go = "GirlEnc_2";						
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях

					// --> belamour ночной приключенец
					if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum") && npchar.index == pchar.GenQuest.NightAdventureSolNum)
					{
						dialog.text = "A vida de um soldado é programada - ficar de guarda, patrulhar ... O que você quer, "+GetAddress_Form(NPChar)+"?";
						link.l1 = "Escuta, foi você quem se meteu numa briga com aquele bêbado aqui recentemente? Bom, pelo visto, sim, foi você mesmo...";
						link.l1.go = "NightAdventure_CitizenHomieSolder";
						break;
					}
					// <-- ночной приключенец
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Excelência, Governador-Geral! Em que posso servir?";
							link.l1 = "Não preciso de nada, obrigado.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "É uma grande honra para mim, senhor Governador-Geral! Como posso ajudar?";
								link.l1 = "Cumpra seu serviço com dedicação – não exijo mais nada de você.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Que bom vê-lo, Vossa Excelência! Em que um humilde soldado pode servir ao governador-geral das nossas colônias?";
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
							link.l1 = "Calma, soldado, não preciso do seu relatório. Apresente-se ao seu oficial.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Que bom ver você, Vice-Almirante! Posso ajudar em alguma coisa?";
								link.l1 = "Não, eu só estava testando o quanto você está atento. Fico feliz que tenha me reconhecido.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Vice-Almirante, é uma honra para mim! Em que posso ajudar?";
								link.l1 = "Servir "+NationNameGenitive(sti(npchar.nation))+", soldado! É o melhor que você pode fazer.";
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
							dialog.text = "Saudações, capitão! Se tiver alguma ordem para mim, peço desculpas: embora eu esteja a serviço de "+NationNameGenitive(sti(npchar.nation))+", eu só respondo ao comandante e ao governador."; 
							link.l1 = "Meus oficiais e minha tripulação obedecem às minhas ordens. Cumpra seu dever, soldado.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Capitão, posso servir a bordo do seu navio? O mesmo serviço por "+NationNameGenitive(sti(npchar.nation))+", mas eu prefiro o mar."; 
								link.l1 = "Você é necessário onde foi designado, então cumpra seu dever com honra. Feche os olhos por um segundo, e eles levarão isso para o mar.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Ah, que sorte a sua: você é o capitão de um navio a serviço de "+NationNameGenitive(sti(npchar.nation))+"... E eu fico preso aqui o dia todo."; 
								link.l1 = "Você acha que eu simplesmente cheguei no Caribe e virei capitão uma semana depois? Isso aqui são anos de trabalho duro...";
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
							link.l1 = "Tudo bem, tudo bem...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Você vai me contar sobre alguma atividade suspeita?";
							link.l1 = "Não, nenhuma mesmo, e aliás, eu sou capitão. Vejo que você já não está mais ouvindo? Tchau.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Este é um local militar, então não faça muito barulho aqui.";
							link.l1 = "Certo, vou lembrar disso.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Tempo tão bom, e eu aqui parado. Na cidade pelo menos tem garotas, mas aqui? Só tem rato passando.";
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
							link.l1 = "Você vai me contar essa história outra hora. Agora estou com um pouco de pressa.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Cuidado aqui, você está em um forte! Fique quieto como um rato!";
							link.l1 = "Como quiser, soldado.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Ei! Você tem um pouco de água, por acaso? Estou morrendo de sede.";
							link.l1 = "Não, amigo, tenha paciência...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "Como é monótona a vida na guarnição, só tem caipira como você por aqui! Agora, a guarnição da cidade com certeza tem dias melhores...";
							link.l1 = "E você chama isso de 'estar de serviço'? Desse jeito, você vai acabar deixando um espião passar bem na sua frente!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("Você parece ser forte, não é? Gostaria de se alistar para servir na guarnição do forte? Temos alojamentos espaçosos, duas refeições por dia e bebida de graça.","Oh, senhorita, você não faz ideia de como é agradável encontrar uma dama tão encantadora neste fim de mundo!")+"";
							link.l1 = ""+GetSexPhrase("Isso é realmente tentador, mas ainda assim preciso recusar. Toda essa rotina de quartel simplesmente não é pra mim.","Obrigada pelo elogio, soldado.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Esse maldito calor... Eu daria de bom grado metade da minha vida pra voltar pra Europa.";
							link.l1 = "Sim, posso ver que sua saúde não está adaptada ao clima local.";
							link.l1.go = "exit";
						break;

					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Espere um momento. Queria te perguntar uma coisa "+GetSexPhrase("хотел","хотела")+"...";
					link.l3.go = "quests";//(перессылка в файл города) */				
				}
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_DialogeWithSoldierOnPier") && npchar.location.group == "soldiers" && npchar.city == "Bridgetown")
			{
				dialog.text = "Bem-vindo a Bridgetown, "+GetAddress_Form(NPChar)+"...";
				link.l1 = "Eu achei que meu rosto fosse conhecido não só nas colônias francesas... Meu nome é "+GetFullName(pchar)+".";
				link.l1.go = "WildRose_Soldier_1";
				DeleteAttribute(pchar, "questTemp.WildRose_DialogeWithSoldierOnPier");
				DelLandQuestMark(npchar);
			}
			//<-- Дикая Роза
		break;
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Me parece que isso é alguma trapaça. Vamos falar com o comandante, "+GetSexPhrase("companheiro","querida")+", e descobrir tudo...","Hmm... Algo me diz que você não é quem finge ser... Entregue sua arma "+GetAddress_Form(npchar)+", e me siga para uma investigação mais aprofundada!");
			link.l1 = RandPhraseSimple("Vai se ferrar!","Quando dois domingos caírem na mesma semana...");
			link.l1.go = "fight";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Ah, entendi... Está tudo certo, pode seguir em frente, "+GetAddress_Form(pchar)+".","Devo ter ficado um pouco cansado de ficar de vigia... Parece que está tudo bem, "+GetAddress_Form(pchar)+", me desculpe.");
			link.l1 = "Sem problema!";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "vincento":
			dialog.text = RandPhraseSimple("Ah, entendi... Está tudo certo, pode seguir em frente. "+GetAddress_Form(pchar)+".","Vamos ver agora... Bem, parece que está tudo em ordem, "+GetAddress_Form(pchar)+", me desculpe.");
			link.l1 = "Isso vai te ensinar!";
			link.l1.go = "exit";
		break;
		
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Pense bem nisso! Que ousadia! Vir aqui fingindo ser um comerciante! Seu retrato está pendurado em todos os quartéis, seu desgraçado! Desta vez você não vai escapar! Agarrem ele!";
				link.l1 = RandPhraseSimple("Arrgh!..","Bem, você que pediu por isso...");
				link.l1.go = "fight";	
				break;
			}
			if (pchar.location != "LosTeques_town" && findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе 300912
			{
				dialog.text = "Você veio negociar aqui? Posso saber como? Onde está seu navio? Olha, isso tudo parece muito suspeito, e sou obrigado a detê-lo até esclarecermos essa situação. Entregue sua arma e venha comigo!";
				link.l1 = RandPhraseSimple("Vai se foder!","Quando dois domingos caírem na mesma semana...");
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
				dialog.text = "Hmm... Tudo parece estar em ordem. Ainda assim, preciso avisar que sua licença expira hoje. Vou deixar você passar desta vez, mas ainda será necessário obter uma nova licença.";
				link.l1 = "Obrigado, vou providenciar um novo assim que possível.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hum... Está tudo certo. Mas preciso avisar que sua licença vai expirar em breve. Ela é válida só até "+FindRussianDaysString(iTemp)+". Então lembre-se disso, "+GetAddress_Form(npchar)+".";
				link.l1 = "Obrigado, vou providenciar um novo assim que possível.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Bem, está tudo certo. Sua licença é válida por mais "+FindRussianDaysString(iTemp)+". Pode passar.","Está tudo claro, "+GetAddress_Form(npchar)+". Você está livre para entrar e sair da cidade, sua licença ainda é válida por mais "+FindRussianDaysString(iTemp)+". Desculpe incomodar você.","Está tudo certo, "+GetAddress_Form(npchar)+", não vou mais te segurar aqui.");
				link.l1 = RandPhraseSimple("Excelente. Saudações.","Obrigado, oficial.");
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("Ei, camarada, não quebre nada no farol.","Este farol é uma parte muito importante da cidade. Tome cuidado!");
			link.l1 = RandPhraseSimple("Tudo bem, não se preocupe.","Tudo bem, não se preocupe.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("Não chegue muito perto dos canhões - isto aqui é uma instalação militar!","Estranhos não são permitidos perto dos canhões!","Se eu te pegar rondando perto dos canhões, você está acabado!");
			link.l1 = RandPhraseSimple("Entendi.","Certo, entendi.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;

		// --> генератор "A damsel in the jungle"
		case "GirlEnc_1":
			dialog.text = "E quem é você, capitão? Não seria, por acaso, cúmplice do ladrão mais notório deste povoado?";
			link.l1 = "Com quem você acabou de me chamar de cúmplice?! Tá maluco ou o quê?! Ei, tira as mãos da garota!";
			link.l1.go = "GirlEnc_11";
			link.l2 = "Na verdade, eu "+GetSexPhrase("conheci ela","conheci ela")+" recentemente...";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+GetSexPhrase("Senhor","Senhorita")+", temos ordens para detê-la e levá-la à masmorra. E se acha que pode nos impedir, está enganado.";
			link.l1 = "Vamos ver, então...";
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "GirlEnc_12":
			dialog.text = "Ah, é mesmo? Nesse caso, eu aconselho você a conferir seus bolsos. Aquela moça é profissional, sabia";
			link.l1 = "Obrigado, vou fazer isso. Como pude me envergonhar desse jeito...";
			link.l1.go = "GirlEnc_12End";		
		break;		
		
		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "GirlEnc_2":
			dialog.text = ""+GetSexPhrase("Senhor","Senhorita")+", recebemos ordens para encontrar essa senhora e levá-la ao pai dela.";
			link.l1 = "Bem, ordem é ordem - vá em frente, então.";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "Tarde demais para isso, porque eu já estou conversando com o pai dela.";
			link.l2.go = "GirlEnc_21";
		break;
		
		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("JungleGirl", "11");	
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));	
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "GirlEnc_21":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = "Capitão, temos nossas ordens, e se acha que pode nos impedir, está enganado.";
				link.l1 = "Vamos ver, então...";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "Heh, "+GetSexPhrase("você é um homem de sorte","você é uma moça de sorte")+". O pai dela prometeu uma recompensa generosa a quem a trouxer de volta para ele.";
				link.l1 = "Não desanime – ainda há muitas recompensas esperando por você.";
				link.l1.go = "exit";			 
			}
		break;
		
		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;
		// <-- генератор "A damsel in the jungle"
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomieSolder":
			dialog.text = "Sim, está comigo. Deixe ele apodrecer na cadeia e refletir sobre o que fez. E se você veio me ameaçar por causa dele, acredite: eu posso até falar com o comandante do forte.";
			link.l1 = "Sim, não vim aqui para ameaçar, mas para pedir que retire suas acusações contra ele. Veja, ele é um velho conhecido meu, só se embriagou, mas você sabe, para um bêbado, o mar não passa do joelho ...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_1";
		break;
		
		case "NightAdventure_CitizenHomieSolder_1":
			dialog.text = "Quer dizer, ele me deu um olho roxo enquanto eu estava de serviço, e agora ele deve ser solto? Por que isso deveria acontecer?";
			link.l1 = "Que tal quinhentos pesos como um pedido de desculpas pelo comportamento dele?";
			link.l1.go = "NightAdventure_CitizenHomieSolder_2";
		break;
		
		case "NightAdventure_CitizenHomieSolder_2":
			dialog.text = "Você acha mesmo? Ele insultou minha honra, e você acha que isso pode ser perdoado por quinhentos pesos? Acha que minha honra está à venda?";
			link.l1 = "...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_3";
		break;
			
		case "NightAdventure_CitizenHomieSolder_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM")
			{
				DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
				pchar.quest.NightAdventure_SeaExit.over = "yes";
				pchar.quest.NightAdventure_JungleExit.over = "yes";
				SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
				dialog.text = "Não, Capitão, está tudo certo. Ele mereceu. E peço que não me distraia mais das minhas obrigações.";
				link.l1 = "Bem, você está certo.";
				link.l1.go = "exit";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM")
			{
				dialog.text = "Mil. E nem um peso a menos.";
				link.l1 = "Não, talvez eu não esteja pronto para pagar tanto por um simples hematoma.";
				link.l1.go = "NightAdventure_CitizenHomieSolder_3NM";
				if (sti(pchar.money) >= 1000)
				{
					link.l2 = "Oh... Tudo bem, espere um pouco. Aqui está uma pena e um pedaço de pergaminho. Escreva que você está retirando qualquer acusação contra meu amigo.";
					link.l2.go = "NightAdventure_CitizenHomieSolder_3GM";
				}
			}
		break;
		
		case "NightAdventure_CitizenHomieSolder_3NM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			dialog.text = "Então peço que não me distraia mais dos meus deveres.";
			link.l1 = "Eu não vou.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieSolder_3GM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.GenQuest.NightAdventureToPrisoner = true;
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Aqui está.";
			link.l1 = "Boa sorte com o trabalho.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		//--> Дикая Роза
		case "WildRose_Soldier_1":
			if (GetHour() >= 6 && GetHour() <= 21)
			{
				dialog.text = "Ah, é você, capitão... Esse sol me deixou sonolento... Maldito calor!";
			}
			else
			{
				dialog.text = "Não dá pra discordar disso. Mesmo assim, à noite todo mundo parece igual, sabe.";
			}
			link.l1 = "Qual é o problema, soldado? Normalmente o seu tipo nem perde tempo conversando comigo.";
			link.l1.go = "WildRose_Soldier_2";
		break;
		
		case "WildRose_Soldier_2":
			dialog.text = "Ah, sim, "+GetAddress_Form(NPChar)+". Mas eu tenho uma ordem do Lorde Willoughby: preciso avisar todos os recém-chegados à ilha que, há poucos dias, um grupo de escravos fugiu da plantação do Bispo. Malditos feitores deviam estar dormindo profundamente enquanto eles arrebentavam as correntes. E logo hoje, que eu devia estar nos braços da minha doce Angelique...";
			link.l1 = "Deixa eu adivinhar: mandaram soldados da guarnição para caçar a propriedade do fazendeiro?";
			link.l1.go = "WildRose_Soldier_3";
		break;
		
		case "WildRose_Soldier_3":
			dialog.text = "Claro... O Bishop também mandou alguns grupos de mercenários pra dentro da mata, mas nem isso bastou pra ele. Prometeu uma bela recompensa pra quem trouxer os escravos de volta. Vivos. Normalmente são os negros que se matam de trabalhar pra ele, mas não faz muito tempo entregaram um grupo de desertores da marinha – não servem muito pra pedreira, mas são espertos o bastante pra sumir da plantação...";
			link.l1 = "Eram brancos?";
			link.l1.go = "WildRose_Soldier_4";
		break;
		
		case "WildRose_Soldier_4":
			dialog.text = "Brancos como leite, pode apostar! Os negros teriam simplesmente fugido, mas esses pegaram alguns mosquetes e sabres dos mercenários mortos – e já botaram pra usar. Derrubaram um dos nossos, e também uns capangas do Bispo – o que deixou o resto deles fora de si.\nQuase atiraram nos próprios homens por engano, achando que eram os fugitivos. E alguns civis sumiram sem deixar rastro na mata.";
			link.l1 = "As portas da cidade estão trancadas?";
			link.l1.go = "WildRose_Soldier_5";
		break;
		
		case "WildRose_Soldier_5":
			dialog.text = "Não, claro que não – a cidade não está sitiada. Você é livre para ir onde quiser. Mas se decidir caçar os fugitivos e acabar no meio do fogo cruzado, não venha reclamar depois. E se sobreviver, nem se dê ao trabalho de bater na residência para se queixar com Sua Senhoria – afinal, ele já demonstrou boa vontade cuidando não só dos cidadãos de Bridgetown, mas também dos visitantes.";
			link.l1 = "Que... generoso da parte dele. Deus salve Francis Willoughby!";
			link.l1.go = "WildRose_Soldier_6";
			link.l2 = "Ah, se todos os governadores se importassem tanto com os recém-chegados quanto Sir Willoughby!..";
			link.l2.go = "WildRose_Soldier_7";
		break;
		
		case "WildRose_Soldier_6":
			dialog.text = "Muito engraçado. Pode ir, capitão.";
			link.l1 = "Adeus então, soldado.";
			link.l1.go = "WildRose_Soldier_8";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "WildRose_Soldier_7":
			dialog.text = "É, teríamos bem menos trabalho pela frente. Não vou te segurar mais, capitão.";
			link.l1 = "Boa sorte, soldado.";
			link.l1.go = "WildRose_Soldier_8";
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
		break;
		
		case "WildRose_Soldier_8":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves");
		break;
		//<-- Дикая Роза
		
		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
			dialog.text = "Capitão, peço que guarde suas armas: é proibido sacá-las na nossa cidade.";
			link.l1 = LinkRandPhrase("Certo, vou guardar isso...","Já está feito.","Como você disser...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Vai se ferrar!","Acho que vou usar isso!","Vou guardar quando chegar a hora certa.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("Ei, qual é a dessa agitação com as armas?! Guarde isso agora mesmo!","Eu ordeno que você guarde sua arma imediatamente!","Ei, "+GetAddress_Form(NPChar)+", pare de assustar as pessoas! Guarde sua arma.");
			link.l1 = LinkRandPhrase("Certo, vou guardar isso...","Já está feito.","Como você quiser...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Vai se ferrar!","Acho que vou usar isso!","Vou guardar quando chegar a hora certa.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;
	}
}
