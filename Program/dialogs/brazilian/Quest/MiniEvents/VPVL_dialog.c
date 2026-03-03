
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
		////// Леа Карно //////
		
		case "Exit":
			DialogExit();
		break;
		
		case "First Time":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"! Com licença, você é um vela"+GetSexPhrase("ou","oress")+"?";
			link.l1 = "Eu sou o Capitão "+GetFullName(pchar)+", ao seu dispor.";
			link.l1.go = "Lea First Talk";
			DelLandQuestMark(npchar);
		break;

		case "Lea First Talk":
			dialog.text = "Eu sou Lea. Lea Carno... "+GetSexPhrase("Monsieur","Mademoiselle")+" Capitão, você chegou recentemente? Não viu um barco de pesca chamado 'Cormorant' no mar, viu? Sabe, meu marido... meu marido Pierre... ele partiu há dois dias e ainda não voltou.";
			link.l1 = "O 'Cormorant'? Não, nunca ouvi falar de tal embarcação. Esse nome eu lembraria. Sinto muito, madame. Espero que seu marido esteja bem e apenas tenha se atrasado no caminho.";
			link.l1.go = "Lea First Talk Rep Plus";
			link.l2 = "O 'Cormorant'? Ha! Esse é o nome do barco ou um apelido para o dono? De qualquer forma, nunca vi nenhum dos dois.";
			link.l2.go = "Lea First Talk Rep Minus";
		break;

		case "Lea First Talk Rep Plus":
			dialog.text = "Eu não sei o que pensar... Ele nunca ficou tanto tempo fora. Sempre voltava antes do meio-dia, sem falta. Agora... aconteceu alguma coisa. Eu sinto.";
			link.l1 = "Procure as autoridades. Eles podem enviar um navio de patrulha para vasculhar as águas costeiras.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
		break;

		case "Lea First Talk Rep Minus":
			dialog.text = "Eu não sei o que pensar... Ele nunca ficou tanto tempo fora. Sempre voltava antes do meio-dia, sem falta. Agora... alguma coisa aconteceu. Eu sinto isso.";
			link.l1 = "Procure as autoridades. Eles podem enviar um navio de patrulha para vasculhar as águas costeiras.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
		break;

		case "Lea First Talk1":
			dialog.text = "Oh, "+GetSexPhrase("Monsieur","Mademoiselle")+" Capitão, é claro que já falei com o comandante. Mas de que adiantou? Ele só deu de ombros... Disse que não tinha navios disponíveis para procurar meu marido.\nE eu? Só me resta ficar aqui, olhando para o horizonte, esperando... e tendo esperança.";
			link.l1 = "Agora, agora, Madame Lea. Não desanime ainda. Acho que posso reservar um dia para ajudá-la a procurar.";
			link.l1.go = "Agree To Help";
			link.l2 = "Por que se preocupar tanto? Vai ver a brisa da manhã o levou para os braços de alguma dama encantadora. Ele vai dar uma volta, respirar o ar fresco e voltar.";
			link.l2.go = "bad joke";
			link.l3 = "Quer um conselho? Pare de forçar os olhos olhando pro horizonte. Vá até a taverna em Le François e procure seu querido marido por lá. Não leve a mal, mas provavelmente ele só precisava de um tempo longe das preocupações de casa, e você está transformando isso numa tragédia. Boa sorte.";
			link.l3.go = "Rejection";
		break;

		case "Agree To Help":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Capitão, eu... eu nem sei como te agradecer... Você... você não faz ideia do que isso significa pra mim! Todo mundo só dá de ombros... Mas você... você está disposto a ajudar. Obrigado!";
			link.l1 = "Não precisa me agradecer ainda. Só me diga—onde seu marido costumava pescar? Ele tinha um lugar certo, ou gostava de explorar?";
			link.l1.go = "Go To Help";
		break;
		
		case "bad joke":
			dialog.text = "Uma dama encantadora?! Você acha mesmo que esse é o momento certo para brincadeiras? Eu sei que ele está em apuros... e você ri da minha tristeza! (chora) Parece que tudo no mundo está contra mim agora. Ninguém quer ajudar... Ninguém entende o peso que carrego no coração.";
			link.l1 = "Madame Lea, pelo amor de Deus, me perdoe pela minha falta de cuidado. Não quis ofender! Juro que vou procurar seu marido. Só me diga por onde começar.";
			link.l1.go = "bad joke1";
		break;

		case "bad joke1":
			dialog.text = "Você...? Você realmente quer me ajudar?";
			link.l1 = "Claro. É o mínimo que posso fazer para me redimir pela minha piada imperdoável e fora de hora.";
			link.l1.go = "bad joke2";
		break;

		case "bad joke2":
			dialog.text = "Obrigado, "+GetSexPhrase("Monsieur","Mademoiselle")+" Capitão. Obrigado... De verdade, você me pegou de surpresa—não sei nem o que dizer...";
			link.l1 = "Não precisa agradecer ainda. Me diga, onde seu marido costuma pescar? Ele tem um lugar certo ou muda de lugar?";
			link.l1.go = "Go To Help";
		break;

		case "Go To Help":
			dialog.text = "Bem... Pierre... Ele quase nunca me dizia exatamente onde pescava. Chamava de 'o segredo dele'. Mas se isso ajudar a encontrá-lo... Talvez... Eu não sei... Você realmente quer ajudar, não é, "+GetSexPhrase("Monsieur","Mademoiselle")+" Capitão? Sério mesmo?";
			link.l1 = "Você está pensando se deve compartilhar o local secreto de pesca do seu marido? Garanto que o segredo da sua família ficará comigo—dou minha palavra de capitão. Preciso saber onde é para começar a procurar.";
			link.l1.go = "Go To Help1";
		break;

		case "Go To Help1":
			dialog.text = "Você está certo, "+GetSexPhrase("Monsieur","Mademoiselle")+" Capitão... Me perdoe. Aquele lugar significava tanto para o Pierre. Ele sempre dizia que era seu único segredo de verdade, seu pequeno tesouro.\nMas eu sei onde fica. Se isso ajudar a trazê-lo de volta... Ele pescava perto da Baía de Le Marin. Fica na costa sul, não muito longe da cidade. Por favor, eu imploro—encontre-o!";
			link.l1 = "Não se preocupe, Lea. Vou fazer tudo o que estiver ao meu alcance. Ele tinha inimigos? Alguém o ameaçou recentemente?";
			link.l1.go = "Go To Help2";
		break;

		case "Go To Help2":
			dialog.text = "Inimigos? Pierre? Ele é a pessoa mais bondosa que existe! Não faria mal nem a uma mosca... Ele é só um pescador simples. Quem ele poderia ter prejudicado? Eu simplesmente não entendo o que pode ter acontecido... É tudo tão estranho... e assustador...";
			link.l1 = "Não tema, Madame Lea. Vou partir imediatamente. Tenho certeza de que seu marido está seguro. Vou trazê-lo de volta para seus braços amorosos. Seja forte.";
			link.l1.go = "Return Lea Exit";
		break;

		case "Return back to Lea":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Capitão, por favor — você tem alguma notícia? Descobriu alguma coisa? Qualquer coisa mesmo?";
			link.l1 = "Ainda não, infelizmente. Mas continuo procurando, Lea!";
			link.l1.go = "Exit";
		break;
		
		case "Return Lea Exit":
			DialogExit();
			npchar.dialog.currentnode = "Return back to Lea";
			AddQuestRecord("VPVL", "2"); 
			DoQuestCheckDelay("VPVL_Start", 0.1);
			LocatorReloadEnterDisable("FortFrance_Town", "gate_back", true);
		break;
		
		case "Rejection":
			DialogExit();
			npchar.dialog.currentnode = "Rejection1";
			SetTimerCondition("VPVL_ClearLea", 0, 0, 2, false);  // Удаляем Леа через 2 дня
			CloseQuestHeader("VPVL");
		break;
		
		case "Rejection1":
			dialog.text = "O que mais você quer? Já não se divertiu o bastante zombando de uma pobre mulher?";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

		case "Lea second talk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Capitão! Pierre! Ah, que alegria te ver! Você o encontrou!";
			link.l1 = "Madame Lea, permita-me apresentar Pierre Carno, em pessoa. Não posso dizer que ele saiu ileso, mas não tenho dúvidas de que seus cuidados logo vão restaurá-lo.";
			link.l1.go = "Lea second talk1";
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
		break;

		case "Lea second talk1":
			dialog.text = "Pierre! Santa Virgem Maria! Eu fiquei doente de preocupação com você! Onde você esteve? Você está tão pálido... não tem cor nenhuma no seu rosto... Oh! E o que é isso?! Essas feridas horríveis?! Cortes... e queimaduras...";
			link.l1 = "Silencie agora, meu tesouro. São só arranhões, logo vão sumir. Ver seu rosto de novo... era tudo o que eu queria. Se não fosse pelo Capitão... eu devo "+GetSexPhrase("ele","ela")+" minha própria vida.";
			link.l1.go = "Lea second talk2";
			CharacterTurnByChr(npchar, CharacterFromID("VPVL_Pier_carno"));
			sld = CharacterFromID("VPVL_Pier_carno");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_Lea_girl"));
			locCameraFromToPos(-7.62, 3.1, 83.26, false, 30, -15, 0);
		break;

		case "Lea second talk2":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Capitão... Eu... Eu nem sei como te agradecer... você o encontrou! Você salvou meu Pierre! Obrigada... obrigada por tudo! Que o Senhor te proteja, "+GetSexPhrase("Monsieur","Mademoiselle")+" Capitão!";
			link.l1 = "Pronto, pronto, já chega disso. O que o Pierre realmente precisa é de uma boa refeição quente e um descanso de verdade.";
			link.l1.go = "Exit";
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
			AddDialogExitQuest("VPVL_PierTalkOnThePirs");
		break;
		
		//////   Контры   //////
		
		case "Kontr Le Maren":
			dialog.text = "Droga! Finalmente você aparece, "+GetSexPhrase("seu vira-lata imundo","sua desgraçada miserável")+"! Onde diabos você esteve? Estamos torrando nesta praia maldita há três dias! Cadê a nossa carga?!";
			link.l1 = "Parece que a festa não pode começar sem mim, hein, senhores? Bem, posso ter me atrasado um pouco—mas é melhor chegar com a maré do que nunca aparecer!";
			link.l1.go = "Exit_Sneak";
			link.l2 = "Falando comigo, é? Talvez devesse aprender um pouco de educação antes de sair latindo perguntas como um rato de porão!";
			link.l2.go = "Exit_Lucky";
			//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
			locCameraFromToPos(-3.53, 2.35, 6.35, true, 1.93, -0.60, 11.17);
			DeleteAttribute(pchar, "questTemp.VPVL_Contr_V_Lemaren");
		break;
		
		case "Exit_Sneak":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification("Experience gained", SKILL_SNEAK);
		break;
		
		case "Exit_Lucky":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			notification("Experience gained", SKILL_FORTUNE);
		break;

		case "Kontr Le Maren0":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = ""+sld.name+", seu cabeça de vento! Abre os olhos, seu idiota—esse aí não é o nosso contato!";
			link.l1 = "Argh... Mais um dos cachorrinhos do governador! Isso é certo como a maré! Desde "+GetSexPhrase("esse canalha","essa garota tola")+" arrastado "+GetSexPhrase("ele mesmo","ela mesma")+" aqui, vamos puxar "+GetSexPhrase("ele","ela")+" para a caverna com o outro rato. Vamos mostrar "+GetSexPhrase("ele","ela")+" como arrancamos segredos deles—rápido o bastante para que revelem cada plano sujo que o patrão já sonhou!";
			link.l1.go = "Kontr Le Maren1";
			locCameraFromToPos(-3.53, 2.35, 6.35, false, -0.03, 0.40, 7.77);
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_1"));
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_2"));
			
			sld = CharacterFromID("VPVL_contr_1");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_2"));
		break;
		
		case "Kontr Le Maren1":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = "Que ideias podres estão fervendo nessa sua cabeça, seu animal encharcado de sal? Para de babar! Melhor vendermos ela para... você sabe quem. Ele vai pagar um baú de moedas por uma moça dessas, e a gente vai passar um mês inteiro bebendo e se divertindo!";
			if (pchar.sex == "man")
			{
				dialog.text = "O que diabos precisamos de mais um inútil entulhando nossa prisão? Aperte mais o comparsa dele—vai acabar abrindo o bico rapidinho. Quanto a esse aqui, vamos acabar logo com ele aqui mesmo, assim poupamos o trabalho de olhar pra cara dele!";
			}
			link.l1 = "Que mil tubarões famintos devorem suas entranhas, "+sld.name+"! Você é o contrabandista mais astuto de todo o arquipélago!";
			link.l1.go = "Kontr Le Maren2";
		break;

		case "Kontr Le Maren2":
			dialog.text = "...";
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) >= 20)
			{
				if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {
					notification("No pistol equipped", "NONE");
					link.l2 = "Se esse cabeça-de-marisco é o seu melhor sabre, tenho até medo de imaginar as bobagens que passam pela cabeça do resto!";
					link.l2.go = "Kontr Le Maren3";
					CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
					locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
					sld = CharacterFromID("VPVL_contr_1");
					CharacterTurnByChr(sld, CharacterFromID("Blaze"));
					CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
				}
				else
				{
					link.l1 = "(Para mim mesmo)(Pistolas) Enquanto esses ratos do mar tagarelam com suas conversas inúteis, tenho a chance de atacar rápido e certeiro, como um raio em céu limpo.";
					link.l1.go = "murder";
					notification("Check passed", SKILL_PISTOL);
					locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
				}
			}
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) < 20)
			{
				notification("Skill too low (20)", SKILL_PISTOL);
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				sld = CharacterFromID("VPVL_contr_2");
				CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
				CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
			}
			link.l2 = "Se esse cabeça-de-marisco é o seu melhor espadachim, temo imaginar as besteiras que passam pela cabeça do resto!";
			link.l2.go = "Kontr Le Maren3";
		break;
		
		case "Kontr Le Maren3":
			dialog.text = "Vou arrancar essa língua atrevida da sua cabeça, seu cachorro insolente"+GetSexPhrase("","—vadia imunda")+", e vou dar de comer às gaivotas para que você nunca mais diga uma palavra!";
			link.l1 = "Vai encarar, é? Então venha, se tiver coragem de dançar com o diabo.";
			link.l1.go = "Kontr Le Maren Fight";
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
		break;
		
		case "Kontr Le Maren Fight":
			DialogExit();
			AddDialogExitQuest("VPVL_EveryoneFight");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false);
			EndQuestMovie();
		break;
		
		case "murder":
			DialogExit();
			AddDialogExitQuest("VPVL_Pistol_Murder");
			//locCameraFromToPos(-5.04, 2.62, 8.65, false, 20, -6, -15);
		break;
		
		/////////////   Пьер Карно   /////////////
		
		case "PierFirstTalk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"... Me perdoe... Estou desnorteado... Você veio terminar o que eles começaram?";
			link.l1 = "Você é Pierre Carno?";
			link.l1.go = "Pier_1";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.VPVL_SetFlagLeMaren");
		break;

		case "Pier_1":
			dialog.text = "Sou eu mesmo. Você sabe meu nome?";
			link.l1 = "Claro. Caso contrário, o que eu estaria fazendo aqui?";
			link.l1.go = "Pier_2";
		break;

		case "Pier_2":
			dialog.text = "Me perdoe, eu não entendo nada... A dor e a fome tiraram meu juízo... Por que você veio?";
			link.l1 = "É simples. Desde o seu desaparecimento, sua fiel esposa tem vigiado o cais, sempre de olhos atentos procurando pela vela do Cormorant. A tristeza dela me tocou tão fundo que não consegui simplesmente passar e seguir viagem — decidi procurar por você.";
			link.l1.go = "Pier_3";
		break;

		case "Pier_3":
			dialog.text = "Minha esposa... minha querida Léa... Eu tinha certeza de que nunca mais a veria...";
			link.l1 = "Essa maré já passou. Ela está te esperando no cais, ainda agarrada à esperança. Vamos sair daqui. Segure no meu braço.";
			link.l1.go = "Pier_4";
		break;

		case "Pier_4":
			dialog.text = "Piedade... "+GetSexPhrase("Monsieur","Mademoiselle")+"... Eu preciso de um momento... minhas pernas estão como madeira à deriva... Obrigado, de verdade. Se não fosse por você... parece que o próprio Todo-Poderoso te enviou... Você ainda não me disse seu nome. Como devo chamar meu salvador?";
			link.l1 = "Capitão "+GetFullName(pchar)+". Enquanto recupera suas forças, me conte como veio parar aqui. Estava fazendo negócios com esses... homens?";
			link.l1.go = "Pier_5";
			LAi_Fade("VPVL_PierStay", "");
		break;

		case "Pier_5":
			dialog.text = "Céus, não, Capitão. Sou apenas um pescador humilde. O dia começou tão bem. Eu pescava na costa oeste — a pescaria estava incrível.\nEstava ansioso para barricar o peixe e lançar as redes de novo, mas não percebi a corrente puxando meu barco para o recife. O casco era fino como casca de ovo — um golpe bastou para deixar o mar entrar. O Cormorão, pesado com a pesca da manhã, afundou rápido.";
			link.l1 = "Então você conseguiu chegar à terra, só para os contrabandistas acharem que você era um dos espiões do governador?";
			link.l1.go = "Pier_6";
		break;

		case "Pier_6":
			dialog.text = "Exatamente. Mal consegui chegar à praia, arrastado pelas malditas ondas. Só precisava me secar e descansar um pouco antes de ir para a cidade. Então, aqueles demônios apareceram do nada.\nBastou um olhar para decidirem que eu era um espião. Não tive nem chance de dizer uma palavra antes de me amarrarem e me arrastarem até aqui. Me deixaram sem comer e me torturaram por dois dias, tentando me forçar a confessar coisas das quais eu não fazia ideia—agentes, planos... mas eu não sabia de nada!";
			link.l1 = "Cérebro era coisa rara entre aquele bando—por isso agora servem de comida pros caranguejos. Mas isso ficou pra trás. Agora você está livre. Hora de reencontrar sua esposa—ela deve estar desesperada de preocupação.";
			link.l1.go = "Pier_7";
		break;

		case "Pier_7":
			dialog.text = "Tudo o que eu quero é abraçá-la de novo. Acho que... acho que já consigo andar agora.";
			link.l1 = "Então não vamos perder mais tempo.";
			link.l1.go = "exit_grot";
		break;
		
		case "exit_grot":
			DialogExit();  
			AddQuestRecord("VPVL", "4");
			AddDialogExitQuest("VPVL_PierFollow");
		break;
		
		case "PierInThePirs":
			dialog.text = "Capitão, eu lhe suplico—venha à taverna amanhã à noite, às seis badaladas. Minha consciência nunca ficaria em paz se eu não lhe agradecesse como merece. Agora... não encontro palavras para expressar o que sinto no coração. Por favor, venha. Isso significaria muito para mim.";
			link.l1 = "Muito bem, Pierre. Não se preocupe—eu estarei lá.";
			link.l1.go = "GoHome";
			locCameraFromToPos(-8.28, 3.1, 82.93, false, 40, -15, 0);
		break;

		case "GoHome":
			DialogExit();
			AddQuestRecord("VPVL", "5");
			AddDialogExitQuest("VPVL_KarnoGoHome");
		break;

		case "PierTalkTavern":
			dialog.text = "Capitão! Você veio! Por favor, sente-se comigo!";
			link.l1 = "Com prazer!";
			link.l1.go = "PierTalkTavern1";
			LAi_Fade("VPVL_SitOnTheTable", "");
			FreeSitLocator("FortFrance_Tavern", "sit6");  // Just in case
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			pchar.questTemp.VPVL_DontSpawnSmugglersShipPier = true;
			DelLandQuestMark(npchar);
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
		break;

		case "PierTalkTavern1":
			dialog.text = "Vamos erguer nossas canecas à sua contínua boa sorte e saúde!";
			link.l1 = "Não só à minha, Pierre—mas à sua também. Você está com uma aparência bem melhor do que quando te encontrei naquela caverna miserável. Saúde!";
			link.l1.go = "PierTalkTavern2";
		break;

		case "PierTalkTavern2":
			dialog.text = "Capitão, não sei nem como agradecer por tudo! Você não me ignorou, não virou as costas—ajudou um completo desconhecido, um simples pescador. Uma atitude tão nobre merece uma recompensa à altura, e quero lhe dar tudo o que tenho.\nAqui—vinte pedaços de âmbar dourado como o sol e cinco pedras azuis raras, resgatadas de um navio naufragado. Agora são suas.\nTambém quero que fique com meus instrumentos de navegação e apetrechos de pesca. Não tenho mais barco, então não me servem para nada.";
			link.l1 = "Obrigado, Pierre. Isso com certeza vai ser útil. Mas o mais importante é que você está em casa de novo—e sua esposa não precisa mais viver com medo. As coisas vão melhorar para vocês dois.";
			link.l1.go = "PierTakeGift";
			link.l2 = "Pierre, eu agradeço o gesto, mas você deve ficar com elas. Vai precisar de cada moeda para consertar seu barco, comprar anzóis, redes, barris... Seu agradecimento—e ver você e sua esposa juntos de novo—já é recompensa suficiente. Cuidem um do outro.";
			link.l2.go = "PierWontGift1";
		break;
		
		case "PierTakeGift":
			dialog.text = "Eu ainda não consigo acreditar que tudo isso realmente aconteceu... Vamos brindar a um novo capítulo na vida da minha família—e ao seu coração nobre, Capitão!";
			link.l1 = "E à boa sorte, Pierre. Todos nós precisamos um pouco dela!";
			link.l1.go = "ZastavkaVPVL";
			AddItems(PChar, "jewelry8", 20);
			AddItems(PChar, "jewelry7", 5);
			AddItems(PChar, "A_map_martiniqua", 1);
			AddItems(PChar, "spyglass3", 1);
			AddItems(PChar, "obereg_7", 1);
		break;

		case "PierWontGift1":
			dialog.text = "Capitão, não posso deixar as coisas assim... Você salvou minha vida, e eu lhe devo tudo. Já que recusa o âmbar e outros presentes, permita ao menos que eu ensine sua tripulação a pescar nas águas rasas. Isso vai mantê-los alimentados e aliviar seus gastos com mantimentos. O que me diz?";
			link.l1 = "Agora sim, essa é uma ótima ideia! Como diz o velho ditado—ensine alguém a lançar uma rede, e nunca mais vai passar fome.";
			link.l1.go = "PierWontGift2";
			pchar.questTemp.VPVL_Food = true;
		break;

		case "PierWontGift2":
			dialog.text = "Bem dito, Capitão! Fico feliz em ser útil. Agora—vamos tomar mais uma taça?";
			link.l1 = "À sua saúde e prosperidade, Pierre!";
			link.l1.go = "ZastavkaVPVL";
		break;
		
		case "ZastavkaVPVL":
			DialogExit();
			SetLaunchFrameFormParam("Four hours have passed...", "VPVL_SitOnTheTable", 2, 2);
			LaunchFrameForm();
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
			sld = CharacterFromID("VPVL_Pier_carno");
			sld.dialog.currentnode = "PierTalkTavern3";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;
		
		case "PierTalkTavern3":
			if(CheckAttribute(pchar, "questTemp.VPVL_Food"))
			{
			int foodDays = CalculateShipFood(&pchar);
			dialog.text = "Pelo tridente de Netuno! Que grogue forte! Mais um ou dois goles e eu... hic... vou acabar cantando uma canção tão alta que até o kraken vai acordar! Todo mundo daqui até o porto vai ouvir minha voz!";
			link.l1 = "Guarde essa cantoria para águas mais calmas, Pierre. Poupe sua voz para... hic... nosso próximo porto. Se você começar a desafinar, logo estarei cantando junto. E eu tenho... er... assuntos urgentes me esperando. A maré não espera por ninguém... hic... nem por quem já está com o vento na cabeça! Fique em bons ventos... hic... e cuide bem daquela sua boa mulher também!";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			notification("Ship's provisions consumption reduced by 15%", "None");
			}
			else
			{
			dialog.text = "Pelo tridente de Netuno! Que grogue forte! Mais um ou dois goles e eu... hic... vou acabar cantando uma canção de marinheiro que até o kraken vai acordar! Todo mundo daqui até o porto vai ouvir minha voz!";
			link.l1 = "Guarda essa cantoria para águas mais calmas, Pierre. Poupe sua voz para... hic... nosso próximo porto. Se você começar a desafinar, logo estarei acompanhando o coro. E eu tenho... er... assuntos urgentes me chamando. A maré não espera por ninguém... hic... nem mesmo quem está com o vento nas ideias! Fique em bons ventos... hic... e cuide bem daquela sua boa mulher também!";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			}
		break;

		case "PierTalkTavern4":
			dialog.text = "Capitão... você tem o coração de um... hic... verdadeiro marinheiro, tem mesmo! Minha dívida com você nunca poderá ser paga, ouviu? Se lançar âncora no nosso porto de novo... nosso lar... nosso lar será seu como se tivesse nascido da mesma... da mesma mãe! Pela minha alma e honra! Vamos brindar juntos de novo quando a Fortuna te trouxer de volta a estas terras!";
			link.l1 = "Devagar e sempre, Pierre! É melhor eu... hic... levantar âncora antes que minhas pernas de marinheiro virem geleia e eu acabe à deriva no chão desta taverna! Que bons ventos encham suas velas!";
			npchar.dialog.currentnode = "RepeatTavern";
			link.l1.go = "Exit2";
		break;

		case "Exit2":
			DialogExit();
			LAi_Fade("VPVL_ExitFromTableVPVL", "VPVL_PierLivingTavern");
			DeleteAttribute(pchar, "questTemp.VPVL_Delete_Ship_RemoveFlag");
		break;

		case "RepeatTavern":
			dialog.text = "Too-o-o, o mar azul pro-fun-do, e os ventos alísios... hic... seguimos para os pesqueiros ao raiar do dia!.. Maldição, esse rum já me deixou tonto! As estrofes me fogem! Capitão!.. Ainda está ancorado aqui, é? Taberneiro! Traga... hic... o melhor destilado das Índias Ocidentais que tiver na adega!";
			link.l1 = "Estou indo embora, Pierre! Hic... enquanto ainda consigo navegar pelo caminho traiçoeiro de volta ao meu navio sem encalhar nos recifes!";
			link.l1.go = "Exit";
		break;

		case "MeetingInTneCity":
			dialog.text = ""+pchar.name+"! Uma visão para estes olhos marcados pelo sal! Que tal um gole do melhor rum do Caribe? Para celebrar nosso encontro neste vasto oceano da vida!";
			link.l1 = "Seu rosto marcado pelo tempo também alegra meu coração, Pierre. Mas, infelizmente, o dever exige minha sobriedade hoje. Meu caminho está traçado por águas traiçoeiras que pedem uma mente clara e mão firme. Quem sabe quando nossos destinos se cruzarem novamente?";
			link.l1.go = "MeetingInTneCity1";
		break;

		case "MeetingInTneCity1":
			dialog.text = "Ayou, ayou, Capitão! Um navio precisa navegar antes de atracar. Primeiro o livro-caixa, depois o descanso, como dizem os mercadores. Mas quando a Fortuna girar sua roda para o nosso lado de novo, vamos brindar de um jeito que até o velho Barba Negra ficaria orgulhoso!";
			link.l1 = "Anote isso no diário de bordo, Pierre. Até que as marés nos unam novamente!";
			link.l1.go = "Exit";
			npchar.dialog.currentnode = "ExitRepeat";
		break;

		case "ExitRepeat":
			dialog.text = "Capitão! Seu navio encontrou abrigo seguro da tempestade de obrigações?";
			link.l1 = "A maré do comércio ainda puxa minha âncora, Pierre. Meus deveres me mantêm preso ao leme por mais um tempo.";
			link.l1.go = "Exit";
		break;
	}
}   