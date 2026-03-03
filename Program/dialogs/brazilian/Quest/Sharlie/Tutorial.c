void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold;
	string attrL, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{	case "First time":
			dialog.text = "Você quer alguma coisa?";
			link.l1 = "Não, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> Шарль на носу корабля, Алонсо подходит с диалогом
		case "StartSailor":
			dialog.text = "Uma bela visão, hein?";
			link.l1 = "Esse maldito mar está tentando me matar faz dois meses. Ainda não conseguiu.";
			link.l1.go = "StartSailor_1_fencing";
			link.l2 = "É verdade. Às vezes o oceano nos lembra de como somos pequenos.";
			link.l2.go = "StartSailor_1_leadership";
			link.l3 = "Aprendi que só existem dois estados no mar: tédio ou terror. Isso... é diferente.";
			link.l3.go = "StartSailor_1_fortune";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "StartSailor_1_fencing":
			dialog.text = "Ha! Primeira vez no mar, monsieur? Quando está calmo assim, qualquer um pode bancar o capitão. Aproveite enquanto dura.";
			link.l1 = ""+GetFullName(pchar)+". Um nobre, fique sabendo. Não venha me chamar de 'monsieur'.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_1_leadership":
			dialog.text = "Ha! Primeira vez no mar, monsieur? Quando está calmo assim, qualquer um pode bancar o capitão. Melhor aproveitar enquanto dura.";
			link.l1 = ""+GetFullName(pchar)+". Um nobre, só pra você saber. Não venha me chamar de 'monsieur'.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_1_fortune":
			dialog.text = "Ha! Primeira vez no mar, monsieur? Quando está calmo assim, qualquer um pode bancar o capitão. Melhor aproveitar enquanto dura.";
			link.l1 = ""+GetFullName(pchar)+". Um nobre, só pra você saber. Não venha me chamar de 'monsieur'.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_2":
			dialog.text = "Como desejar, meu senhor. Então, sua primeira viagem, meu senhor "+pchar.lastname+"?";
			link.l1 = "É tão óbvio assim? Sim, é a minha primeira vez. E eu definitivamente não nasci para cabines apertadas e comida mofada de navio.";
			link.l1.go = "StartSailor_3";
		break;
		
		case "StartSailor_3":
			dialog.text = "Está na cara que você é um marinheiro de primeira viagem, meu senhor.";
			link.l1 = "Cuide da sua língua! A um homem de honra, eu jogaria minha luva e exigiria satisfação. Mas para um camponês como você – vou simplesmente cortar suas orelhas.";
			link.l1.go = "StartSailor_4";
		break;
		
		case "StartSailor_4":
			dialog.text = "Talvez em Paris. Mas aqui, palavras assim podem fazer um homem virar comida de peixe. Eu não sairia balançando essa lâmina por aí, meu senhor – e não faça o capitão se arrepender de ter deixado você andar armado no convés. O último encrenqueiro foi jogado no porão com pão bolorento e água de sentina que nem os ratos queriam. E sabe de uma coisa? O coitado ainda teve que pagar mais quando chegamos ao porto.";
			link.l1 = "O que eu podia esperar... Tá bom, vamos esquecer esse mal-entendido. Preciso ficar lembrando que esse barco está longe de ser o Louvre.";
			link.l1.go = "StartSailor_5";
		break;
		
				case "StartSailor_5":
			dialog.text = "É? O Louvre? O que isso deveria ser?";
			link.l1 = "Ha! O Louvre é um palácio para poucos escolhidos. Bailes, recepções, intrigas...";
			link.l1.go = "StartSailor_6";
		break;
		
		case "StartSailor_6":
			dialog.text = "Ah... um bordel então. Temos muitos desses por aqui. Não posso dizer que são só para os escolhidos – pague sua moeda e é tudo seu.";
			link.l1 = "Ha! Você não está muito longe da verdade, marinheiro.";
			link.l1.go = "StartSailor_7";
		break;
		
		case "StartSailor_7":
			dialog.text = "Meu nome é Alonso, aliás. E o que traz você até os confins do mundo, meu senhor? Duvido que tenha cruzado o Atlântico só para discutir com um marinheiro.";
			link.l1 = "Meu pai está doente e não pode sair da nossa propriedade na Gasconha. Fui encarregado de encontrar meu... irmão mais velho. Ele veio para cá a negócios e, desde então, não tivemos mais notícias dele.";
			link.l1.go = "StartSailor_8";
		break;
		
		case "StartSailor_8":
			dialog.text = "Por que não simplesmente enviar um homem de confiança, em vez de enfrentar você mesmo as durezas do mar?";
			link.l1 = "A família vem em primeiro lugar. Não posso confiar seu destino ao primeiro homem que encontrar.";
			link.l1.go = "StartSailor_9_nobilityplus";
			link.l2 = "Eu até gostaria – mas meu pai insiste que tem que ser eu. Não faço ideia do porquê.";
			link.l2.go = "StartSailor_9_nobilityminus";
		break;
		
		case "StartSailor_9_nobilityplus":
			dialog.text = "E qual é o nome do seu irmão?";
			link.l1 = "Michel de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "StartSailor_9_nobilityminus":
			dialog.text = "E qual é o nome do seu irmão?";
			link.l1 = "Michel de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "StartSailor_10":
			dialog.text = "De Monper? E você é "+pchar.lastname+"? Como assim?";
			link.l1 = "Não me olhe assim. Eu sou o filho legítimo. Só fiquei com o sobrenome da minha mãe.";
			link.l1.go = "StartSailor_11";
		break;
		
		case "StartSailor_11":
			dialog.text = "Nada para se envergonhar. Você vai se encaixar perfeitamente – no Novo Mundo, todo mundo tem uma história. Eu, por exemplo...";
			link.l1 = "Eu não tenho vergonha de nada! Só me fale sobre a Martinica. É uma cidade grande? Tipo Toulouse?";
			link.l1.go = "StartSailor_12";
		break;
		
		case "StartSailor_12":
			dialog.text = "Uma cidade? Ha! Martinica é uma ilha. Uma das maiores possessões francesas no Caribe. Lá eles cultivam um café ardente, extraem enxofre infernal e dão ao mundo as mulheres mais lindas que já vi. Uma combinação e tanto, se quer saber.";
			link.l1 = "Não estou interessado em café ou enxofre. Mas espere... uma ilha? Como é que vou encontrar meu irmão numa ilha inteira?";
			link.l1.go = "StartSailor_13";
		break;
		
		case "StartSailor_13":
			dialog.text = "Não se preocupe. Saint-Pierre é uma cidade pequena — não é o Louvre, claro, mas também não é a selva. Agora, Le François, Deus me livre — um homem decente não tem o que fazer lá.";
			link.l1 = "Se for preciso, vou atrás dos bandidos. Michel sempre me tirou das enrascadas. Agora é a minha vez.";
			link.l1.go = "StartSailor_14";
		break;
		
		case "StartSailor_14":
			dialog.text = "Nada mal... para um novato em alto-mar.";
			link.l1 = "Lá vai você de novo. Quanto tempo falta até chegarmos a essa maldita Martinica?";
			link.l1.go = "StartSailor_15";
		break;
		
		case "StartSailor_15":
			dialog.text = "Cinco dias.";
			link.l1 = "Cinco?!";
			link.l1.go = "StartSailor_16";
		break;
		
		case "StartSailor_16":
			dialog.text = "Pelo menos isso. E se aparecerem piratas — talvez nem cheguemos ao destino. As Pequenas Antilhas são águas perigosas, mesmo sem carga valiosa.";
			link.l1 = "Fora os passageiros!";
			link.l1.go = "StartSailor_17";
		break;
		
		case "StartSailor_17":
			dialog.text = "Ha-ha! Não se preocupe. Na pior das hipóteses, eu mesmo te escondo no porão — nenhum pirata pensaria em procurar um nobre gascão entre barris de rum! Afinal, não somos idiotas — misturar um gascão vivo com rum. Isso explodiria pior que pólvora, ha-ha!";
			link.l1 = "Ha! Ainda bem que o rum acabou faz um mês!";
			link.l1.go = "StartSailor_18";
		break;
		
		case "StartSailor_18":
			dialog.text = "É... melhor não falar essas coisas em voz alta. O pessoal pode achar que foi por sua causa que ficamos sem rum.";
			link.l1 = "Tá bom, Alonso, eu não vou. Nem beberia essa porcaria mesmo. E quanto ao seu plano genial de me esconder no porão antes da batalha — esquece.";
			link.l1.go = "StartSailor_20";
		break;
		
		case "StartSailor_20":
			dialog.text = "Por que não?";
			link.l1 = "Sou um nobre, sei manejar uma espada e não estou me escondendo no porão.";
			link.l1.go = "StartSailor_21_fencing";
			link.l2 = "Se for preciso — vou defender o navio e lutar junto com os outros. O que mais?";
			link.l2.go = "StartSailor_21_leadership";
			link.l3 = "Eu mesmo vou decidir quando lutar e quando fugir. Vamos ver no que dá.";
			link.l3.go = "StartSailor_21_fortune";
			locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
		break;
		
		case "StartSailor_21_fencing":
			dialog.text = "Ha. Talvez você tenha mais a oferecer do que parece. Mas cuidado — o Caribe adora despedaçar quem chega aqui de nariz empinado. Você não vai sobreviver ao primeiro encontro com a linha de frente dos piratas. Aliás, algum bandido esfarrapado nos arredores de Saint-Pierre pode te abrir no meio antes que perceba.";
			link.l1 = "Você não me conhece nem um pouco.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "StartSailor_21_leadership":
			dialog.text = "Ha. Talvez você tenha mais a oferecer do que parece. Mas cuidado — o Caribe adora despedaçar quem chega aqui de nariz empinado. Você não vai sobreviver ao primeiro encontro com a vanguarda pirata. Aliás, algum bandido esfarrapado nos arredores de Saint-Pierre vai te esfaquear antes que perceba.";
			link.l1 = "Você não me conhece nem um pouco.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "StartSailor_21_fortune":
			dialog.text = "Ha. Talvez você tenha mais valor do que parece. Mas cuidado — o Caribe adora despedaçar quem chega aqui de nariz empinado. Você não vai sobreviver ao primeiro encontro com a linha de frente dos piratas. Aliás, algum bandido esfarrapado nos arredores de Saint-Pierre pode te esfaquear antes que perceba.";
			link.l1 = "Você não me conhece nem um pouco.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		case "StartSailor_22":
			dialog.text = "Mas eu conheço o Novo Mundo e seu povo. Se você não pretende murchar atrás de livros de contabilidade ou servir na casa do governador — vai ter que aprender tudo do zero.";
			link.l1 = "Ainda bem que não pretendo ficar por aqui.";
			link.l1.go = "StartSailor_23";
		break;
		
		case "StartSailor_23":
			dialog.text = "É isso que você pensa. Não costumamos levar passageiros de volta para a Europa. Alguns morrem — de febre, de corda, ou de bala. Outros ficam — para sempre. Já vi aristocratas frágeis virarem capitães, bandidos cruéis se tornarem fazendeiros respeitados. E oficiais brilhantes — acabarem como vagabundos sem um tostão.";
			link.l1 = "Muito tentador, mas vou voltar para a França. Tenho pessoas me esperando.";
			link.l1.go = "StartSailor_24";
		break;
		
		case "StartSailor_24":
			dialog.text = "Ah sim, é verdade. Um pai doente?";
			link.l1 = "Digamos apenas... há uma certa dama cujo marido realmente não me quer em Paris. Mas dê alguns meses — e as paixões vão esfriar.";
			link.l1.go = "StartSailor_25";
		break;
		
		case "StartSailor_25":
			dialog.text = "Ha-ha-ha! Então você veio mesmo ao lugar certo. O Caribe é um paraíso para quem foge de maridos ciumentos. E o tempo voa por aqui. Espere só um pouco — quem sabe você ainda acaba virando marinheiro!";
			link.l1 = "Mais provável que eu seja capitão. Não levo jeito pra ser marinheiro comum, receio. Trabalho braçal não é comigo.";
			link.l1.go = "StartSailor_26";
		break;
		
		case "StartSailor_26":
			dialog.text = "Na França, o poder vem de berço. Mas a bordo de um navio — o capitão é rei, juiz e Deus. Ninguém sabe que provações ele enfrentou para merecer esse chapéu. Aqui, cada um recebe o que merece. Como dizemos no convés — a cada um, o seu.";
			link.l1 = "Besteira. Falando em capitães — preciso conversar com o seu, ainda mais agora que ele anda me procurando. Até logo, Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_StartKino_6");
		break;
		
		// <-- Шарль на носу корабля, матрос подходит с диалогом
		
		// --> С Алонсо можно в любой момент поговорить
		case "AlonsoWait":
			dialog.text = "Queria perguntar alguma coisa?";
			if (PCharDublonsTotal() >= 60 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Alonso"))
			{
				link.l1 = "Eu vim da parte do Monsieur Pinchon.";
				link.l1.go = "AlonsoGold_2";
			}
			link.l2 = "Nada.";
			link.l2.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_2":
			dialog.text = "Ha! Aquele quatro-olhos te meteu nessa também?";
			link.l1 = "Quatro-olhos?";
			link.l1.go = "AlonsoGold_3";
		break;
		
		case "AlonsoGold_3":
			dialog.text = "Você já viu os óculos dele? Exatamente! Mas não me entenda mal — a tripulação respeita o Monsieur Pinchon. Bons médicos sempre são valorizados a bordo. E ele também é um intendente competente.";
			link.l1 = "Que assunto você tem com ele?";
			link.l1.go = "AlonsoGold_4";
		break;
		
		case "AlonsoGold_4":
			dialog.text = "Uhh... Desculpe, mas isso é assunto nosso. Mas pode ficar tranquilo — não estamos infringindo nenhuma lei do navio.";
			link.l1 = "E as leis comuns?";
			link.l1.go = "AlonsoGold_5";
		break;
		
		case "AlonsoGold_5":
			dialog.text = "As leis comuns não se aplicam a nós. Então, quanto foi que eles colocaram na minha conta?";
			if (PCharDublonsTotal() >= 40)
			{
				link.l1 = "40 dobrões.";
				link.l1.go = "AlonsoGold_DatDeneg_3_gold40";
			}
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "50 doblões.";
				link.l2.go = "AlonsoGold_DatDeneg_3_gold50";
			}
			if (PCharDublonsTotal() >= 60)
			{
				link.l3 = "60 dobrões.";
				link.l3.go = "AlonsoGold_DatDeneg_3_gold60";
			}
			// link.l4 = "Preciso conferir tudo de novo. Volto mais tarde.";
			// link.l4.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_DatDeneg_3_gold40":
			dialog.text = "Aí está o ouro. Saint-Pierre, aí vou eu! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(40);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold50":
			dialog.text = "Aí está o ouro. Saint-Pierre, aí vou eu! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold60":
			dialog.text = "Aí está o ouro. Saint-Pierre, aí vou eu! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(60);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoWait_2":
			DialogExit();
			NextDiag.CurrentNode = "AlonsoWait";
		break;
		
		// <-- С Алонсо можно в любой момент поговорить
		
		// --> капитан на корабле, который идёт из Европы
		case "Captain":
			dialog.text = "Ah, Charles. Não estava exatamente com pressa, não é? Quando o capitão do navio quer falar, você deve se apresentar imediatamente. Está tendo dificuldade em seguir ordens?";
			link.l1 = "Não estou acostumado a receber ordens, Capitão.";
			link.l1.go = "Captain_2_fencing";
			link.l2 = "Desculpe, Capitão, fui atrasado.";
			link.l2.go = "Captain_2_leadership";
			link.l3 = "Ficou bem claro que o navio é seu — as regras também.";
			link.l3.go = "Captain_2_sailing";
			if (bBettaTestMode)
			{
				link.l9 = "BetaTest (pular tutorial e começar o jogo em Martinica)";
				link.l9.go = "BetaTest_StartGame";
			}
			pchar.questTemp.SharlieTutorial_CaptainDialog = true;
		break;
		
		case "Captain_2_fencing":
			dialog.text = "Não vou admitir que questionem minha autoridade. Você não faz ideia de quantas vezes a má sorte cai sobre passageiros no mar. Considere-se muito sortudo por eu estar interessado em garantir que chegue são e salvo a Saint-Pierre.";
			link.l1 = "Do que você está falando?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "Captain_2_leadership":
			dialog.text = "Desculpas aceitas. Aproveite o momento. Não vai ver muitos pores do sol assim.";
			link.l1 = "Do que você está falando?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "Captain_2_sailing":
			dialog.text = "Bom ver que você aprendeu alguma coisa nesta viagem. A palavra do capitão é lei — e às vezes ela vale até em terra firme, longe do navio.";
			link.l1 = "Do que você está falando?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		case "Captain_3":
			dialog.text = "Capitão. Por favor, dirija-se a mim de acordo com o protocolo marítimo.";
			link.l1 = "Do que está falando, capitão?";
			link.l1.go = "Captain_4";
		break;
		
		case "Captain_4":
			dialog.text = "Queria informar que baixamos as velas e estamos à deriva. Infelizmente, sua chegada à Martinica vai atrasar alguns dias.";
			link.l1 = "Mas por quê, Capitão?";
			link.l1.go = "Captain_5";
		break;
		
		case "Captain_5":
			dialog.text = "Porque eu decidi assim.";
			link.l1 = "Isso tem alguma relação com o encontro de ontem com o comboio de mercadores indo para aquela... como é mesmo o nome...";
			link.l1.go = "Captain_6";
		break;
		
		case "Captain_6":
			dialog.text = "Capsterville. Escute, "+pchar.name+": precisamos conversar seriamente. Estou convidando você para jantar na minha cabine. O sino vai tocar em breve — aí teremos tempo para conversar como homens civilizados, terminando a última garrafa de vinho do navio.";
			link.l1 = "Obrigado pelo convite. Seria uma honra, Capitão.";
			link.l1.go = "Captain_7";
		break;
		
		case "Captain_7":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Me avise quando estiver pronto. Ainda temos um tempo, então fique à vontade para andar pelo navio — só não atrapalhe minha tripulação no trabalho.";
				npchar.SharlieTutorial_question_0 = true;
				// теперь можно пострелять из пушки
				sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
				SetLocatorEvent(sld.id, "event3", "SharlieTutorial_cannon_1");
			}
			else dialog.text = "Mais alguma pergunta?";
			link.l1 = "(Encerrar tudo) Estou pronto, Capitão. Com você — eu até beberia Borgonha!";
			link.l1.go = "Captain_8";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "O que está observando com tanta atenção por essa luneta... Capitão?";
				link.l2.go = "Captain_7_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Capitão, tive o prazer de conversar com um tal de Alonso. Qual é a função dele a bordo?";
				link.l3.go = "Captain_7_question_2_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
			{
				link.l4 = "Capitão, me fale sobre seu navio. É uma pinassa, não é?";
				link.l4.go = "Captain_7_question_3_1";
			}
			link.l5 = "Até a próxima, Capitão.";
			link.l5.go = "Captain_7_exit";
		break;
		
		case "Captain_7_exit":
			DialogExit();
			NextDiag.CurrentNode = "Captain_7";
			if (!CheckAttribute(npchar, "SharlieTutorial_Zapis"))
			{
				npchar.SharlieTutorial_Zapis = true;
				AddQuestRecord("SharlieTutorial", "0.1");
			}
		break;
		
		case "Captain_7_question_1_1":
			dialog.text = "Nada em especial, só observando o horizonte. Um navio à deriva é presa fácil.";
			link.l1 = "Procurando piratas?";
			link.l1.go = "Captain_7_question_1_2";
		break;
		
		case "Captain_7_question_1_2":
			dialog.text = "Ou espanhóis. Estamos navegando sob a bandeira francesa sem escolta, e as Pequenas Antilhas são um verdadeiro cruzamento — e território de Jacques Barbazon.";
			link.l1 = "Quem é esse? Um governador?";
			link.l1.go = "Captain_7_question_1_3";
		break;
		
		case "Captain_7_question_1_3":
			dialog.text = "Pior ainda — um dos barões piratas. Esses malandros criaram uma espécie de organização e se autodenominam Irmandade da Costa. Dividiram o Caribe em seis partes e colocaram um barão em cada uma, assim evitam se destruir entre si.";
			link.l1 = "Por que as autoridades não fazem nada a respeito disso?";
			link.l1.go = "Captain_7_question_1_4";
		break;
		
		case "Captain_7_question_1_4":
			dialog.text = "Você é ingênuo, "+pchar.name+". A pirataria só existe porque as autoridades locais permitem que eles façam reparos e se reabasteçam em certos portos em troca de uma parte do saque. Não gosto de admitir, mas os únicos que realmente fazem algo contra essa praga negra são os espanhóis. Se não fossem eles, teríamos que equipar nosso navio com canhões caros — e ainda contratar uma escolta.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_1 = true;
		break;
		
		case "Captain_7_question_2_1":
			dialog.text = "Marinheiro experiente. Não sei muito sobre ele, mas posso te dizer uma coisa: se todo homem tem um esqueleto no armário, o Alonso tem um cemitério inteiro.";
			link.l1 = "Parece que você não confia nele.";
			link.l1.go = "Captain_7_question_2_2";
		break;
		
				case "Captain_7_question_2_2":
			dialog.text = "De jeito nenhum. Você acha fácil encontrar homens tão experientes para a tripulação? Leva pelo menos um ano e um contramestre excelente para transformar um bando de bêbados de taverna em algo que pareça minimamente uma tripulação. Além disso, Alonso também é a voz do grupo. Um capitão nem perde tempo falando com os subalternos, mas é burrice — e perigoso — esquecer que os marinheiros comuns também têm seus interesses. Alonso os representa quando é preciso.";
			link.l1 = "E o que acontece se a tripulação ficar insatisfeita?";
			link.l1.go = "Captain_7_question_2_3";
		break;
		
		case "Captain_7_question_2_3":
			dialog.text = "Vão me enforcar, e você só vai levar uma facada. Não fique tão pálido. Enquanto a tripulação recebe o pagamento, comida, bebida e cuidados — o acordo entre capitão e tripulação está cumprido. Não arrisco a vida deles, não castigo por capricho, divido o saque e, às vezes, ainda mimo eles com bebida de graça e folga em terra. É assim que mantemos esse equilíbrio frágil — e por isso o navio sempre chega onde precisa.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		case "Captain_7_question_3_1":
			dialog.text = "Você tocou num ponto sensível, "+pchar.name+"! Eu poderia falar da minha beleza para sempre. Terceira classe, vinte canhões, ótima velocidade — não se deixe enganar pelo ‘mercante’!";
			link.l1 = "Entendi a parte das armas e da velocidade. Mas ‘taxa’? ‘Mercante’?";
			link.l1.go = "Captain_7_question_3_2";
		break;
		
		case "Captain_7_question_3_2":
			dialog.text = "As classes são uma divisão aproximada pelo número de canhões. Um navio de sétima classe mal pode ser chamado de barco, enquanto um de primeira classe é quase uma fortaleza. Mas não vá repetir isso na Europa — especialmente perto de oficiais da marinha.";
			link.l1 = "Por que não? Isso é algum tipo de piada de marinheiro?";
			link.l1.go = "Captain_7_question_3_3";
		break;
		
		case "Captain_7_question_3_3":
			dialog.text = "Vão te achar um completo idiota e vão zombar de você. A verdade é que, em qualquer marinha de verdade, o sistema de patentes é diferente e serve só para navios de guerra. Mas aqui no Caribe, as coisas funcionam do nosso jeito, como sempre.";
			link.l1 = "E o que você quis dizer ao chamar seu navio de 'mercante'?";
			link.l1.go = "Captain_7_question_3_4";
		break;
		
		case "Captain_7_question_3_4":
			dialog.text = "Outro termo vago. Navios de guerra — mais resistentes e atiram melhor. Corsários — atacam e fogem. Mercantes — podem carregar muita carga, tripulação ou canhões, mas precisam fazer concessões, senão ficam lentos demais. Também existem navios versáteis, mas não há muito o que dizer sobre eles além de que se adaptam às necessidades do dono.";
			link.l1 = "Você está ficando animado, Capitão.";
			link.l1.go = "Captain_7_question_3_5";
		break;
		
		case "Captain_7_question_3_5":
			dialog.text = "Eu amo meu navio, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_3 = true;
		break;
			
		case "Captain_8":
			if (IsEquipCharacterByItem(pchar, "hat3"))
			{
				dialog.text = "Bem, sorte sua — só me sobrou o Borgonha... Espere um pouco, "+pchar.name+". Onde você conseguiu meu chapéu velho?!\nEspera. Ei, aí em cima no mastro! O que está acontecendo aí em cima?";
				ChangeCharacterComplexReputation(pchar, "nobility", -1);
			}
			else dialog.text = "Bom, sorte sua — Borgonha é tudo que me restou\nEspera. Ei, lá no alto! O que está acontecendo aí em cima?";
			link.l1 = "...";
			link.l1.go = "Captain_9";
		break;
		
		case "Captain_9":
			DialogExit();
			DelLandQuestMark(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga");
		break;
		
		case "BetaTest_StartGame":	// досрочный выход на сушу
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		
		// <-- капитан на корабле, который идёт из Европы
		
		// --> Диалог с охранником каюты
		case "OhrannikCabin":
			dialog.text = "Perdoe-me, Monsieur de More, mas o senhor não pode entrar aí.";
			link.l1 = "Eu já estive na cabine do capitão antes. Você já devia ter se lembrado disso.";
			link.l1.go = "OhrannikCabin_1";
			link.l2 = "Infelizmente, meu plano astuto falhou. Adeus, marinheiro.";
			link.l2.go = "exit";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 12) NextDiag.TempNode = "OhrannikCabin";
			else NextDiag.TempNode = "OhrannikCabin_again";
			if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikStay"))
			{
				LAi_SetStayType(npchar);
				npchar.SharlieTutorial_OhrannikStay = true;
				DeleteQuestCondition("SharlieTutorial_OhrannikStopaet");
			}
		break;
		
		case "OhrannikCabin_1":
			dialog.text = "Perdoe-me, monsieur, mas as circunstâncias mudaram.";
			link.l1 = "E o que exatamente aconteceu?";
			link.l1.go = "OhrannikCabin_2";
		break;
		
		case "OhrannikCabin_2":
			dialog.text = "Já estamos quase chegando, e o capitão prefere não arriscar que alguém limpe seus pertences e desapareça no covil de bandidos de Le François.";
			link.l1 = "Duvido que o capitão estivesse pensando em mim quando deu essa ordem.";
			link.l1.go = "OhrannikCabin_3";
		break;
		
		case "OhrannikCabin_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 12)
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Bem... você tem razão. E já jantou na cabine do capitão mais de uma vez. Vá em frente, Monsieur de More.";
					link.l1 = "Assim está melhor!";
					link.l1.go = "OhrannikCabin_4";
					Notification_Skill(true, 12, SKILL_LEADERSHIP);
				}
				else
				{
					dialog.text = "Insi... insinua-o quê? Eu não quis dizer nada disso, monsieur de More!";
					link.l1 = "Então você precisa me deixar passar.";
					link.l1.go = "OhrannikCabin_3_1";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Monsieur, certamente o senhor entende que a cabine do capitão não é passagem para qualquer um. Ordens são ordens.";
					link.l1 = "Droga, mal posso esperar pra pisar em terra firme de novo. Isso é humilhante!";
					npchar.SharlieTutorial_OhrannikFail = true;
				}
				else
				{
					dialog.text = "Monsieur, já conversamos sobre isso. Não posso deixar você passar.";
					link.l1 = "Teimoso como sempre, marinheiro. Adeus.";
				}
				link.l1.go = "exit";
				NextDiag.TempNode = "OhrannikCabin_again";
				Notification_Skill(false, 12, SKILL_LEADERSHIP);
			}
		break;
		
		case "OhrannikCabin_3_1":
			dialog.text = "Eh... tudo bem. Suponho que não vai sair nenhum grande mal disso.";
			link.l1 = "Assim está melhor!";
			link.l1.go = "OhrannikCabin_4";
			Notification_Skill(true, 12, SKILL_LEADERSHIP);
		break;
		
		case "OhrannikCabin_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			LocatorReloadEnterDisable("Quest_Ship_deck_Medium_trade", "reload_cabin", false);
		break;
		
		case "OhrannikCabin_again":
			dialog.text = "Mais alguma coisa, monsieur? Não posso deixar você entrar — o capitão está preocupado com seus objetos de valor.";
			link.l1 = "Está insinuando roubo, marinheiro? Cuidado com as palavras. Isso é pura insinuação!";
			if (CheckAttribute(npchar, "SharlieTutorial_OhrannikFail")) link.l1.go = "OhrannikCabin_3";
			else link.l1.go = "OhrannikCabin_1";
			link.l2 = "Nada, marinheiro.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OhrannikCabin_again";
		break;
		
		// <-- Диалог с охранником каюты
		
		// --> матрос ругается на ГГ, который активировал брашпиль
		case "SailorWithWindlass_1":
			dialog.text = "Ei, seu nobre pateta! O que você está fazendo, tentando enfiar o diabo no guincho?!\nVocê chutou a trava com esse seu pé real! Tá querendo afundar todo mundo, é isso?!\nFaz um favor pra gente — não encosta em nada, a não ser que seja num nariz escorrendo francês!";
			link.l1 = "O que é isso, exatamente?";
			link.l1.go = "SailorWithWindlass_2";
		break;
		
		case "SailorWithWindlass_2":
			dialog.text = "É o cabrestante, seu idiota. Ele levanta a âncora. E se não estiver travado — pode despedaçar o navio ou enrolar alguém como sardinha em barril!";
			link.l1 = "Ha... E se você girar pro outro lado — ele baixa a âncora, né?";
			link.l1.go = "SailorWithWindlass_3";
		break;
		
		case "SailorWithWindlass_3":
			dialog.text = "Não, gênio, ela faz o tempo voltar. Pena pra você — você já nasceu!";
			link.l1 = "Bem, ninguém se machucou, certo? Navios são máquinas realmente complexas. Vou tomar mais cuidado.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_windlass_8");
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		// <-- матрос ругается на ГГ, который активировал брашпиль
		
		// --> матрос ругается на ГГ, который активировал пушку
		case "SailorWithCannon_1":
			dialog.text = "Você está olhando para o cano longo desse canhão com o mesmo deslumbramento com que admirou o pôr do sol mais cedo.";
			link.l1 = "Vejo que você gosta de me observar, Alonso. Melhor me contar sobre essa maravilha da engenharia militar.";
			link.l1.go = "SailorWithCannon_2";
		break;

		case "SailorWithCannon_2":
			dialog.text = "Isso é um canhão de dezesseis libras. Nem todo navio de guerra tem um desses.";
			link.l1 = "É fácil acertar alguma coisa com isso?";
			link.l1.go = "SailorWithCannon_3";
		break;

		case "SailorWithCannon_3":
			dialog.text = "A queima-roupa — a gente destrói qualquer coisa. A cem jardas, ainda temos chance. Mais longe que isso — é mais barulho e fogo do que outra coisa, mas já é melhor do que nada.";
			link.l1 = "Cem jardas — e o inimigo pode fazer o mesmo.";
			link.l1.go = "SailorWithCannon_4";
		break;

		case "SailorWithCannon_4":
			dialog.text = "Verdade. Mas tudo depende do trabalho em equipe da tripulação e da habilidade do artilheiro. Pena que o nosso está dormindo — ele te daria uma aula inteira e depois te colocaria no canhão ele mesmo, ha!";
			link.l1 = "O canhoneiro é um oficial, certo?";
			link.l1.go = "SailorWithCannon_5";
		break;

		case "SailorWithCannon_5":
			dialog.text = "Normalmente. Sem pelo menos um artilheiro mais ou menos competente, é melhor evitar brigas — seria mais fácil jogar os canhões no mar e fugir.\nCapitães mercantes raramente têm algo maior que canhões de seis libras — eles confiam em escoltas ou na sorte.\nFaz sentido: sem canhões pesados ou muita munição, o navio navega melhor e sobra mais espaço pra carga e mercadoria.\nSe o nosso capitão não tivesse gastado tanto nessas belezinhas, talvez ainda sobrasse um pouco de rum. Suspiro.";
			link.l1 = "O capitão não dirige o fogo dos canhões pessoalmente?";
			link.l1.go = "SailorWithCannon_6";
		break;

		case "SailorWithCannon_6":
			dialog.text = "Com um bom artilheiro e uma tripulação decente, ele nem precisa. Mas vou te dizer: quando um capitão mira os canhões ele mesmo, em vez de só gritar 'Fogo!' do tombadilho — os navios inimigos acabam cheios de buracos.";
			link.l1 = "Posso disparar um?";
			link.l1.go = "SailorWithCannon_7";
			link.l2 = "Obrigado pela palestra fascinante, Alonso. Você é um verdadeiro baú de sabedoria naval.";
			link.l2.go = "SailorWithCannon_7_exit";
		break;
		
		case "SailorWithCannon_7_exit":
			dialog.text = "Claro! Mas mesmo assim, não mexa no canhão e não deixe a tripulação nervosa.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_11");
		break;

		case "SailorWithCannon_7":
			dialog.text = "Atirar com ela? Improvável. Para disparar um tiro — você precisaria da permissão do capitão. Vou perguntar a ele agora!";
			link.l1 = "Não precisa!";
			link.l1.go = "SailorWithCannon_8";
		break;

		case "SailorWithCannon_8":
			dialog.text = "Caa-apitão!";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieTutorial_cannon_3");
		break;
		
		case "CaptainWithCannon_1":
			dialog.text = "O que foi, Alonso?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_2";
		break;

		case "CaptainWithCannon_2":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_3":
			dialog.text = "O senhor Charles sugere disparar o canhão — estritamente para fins de treinamento.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_4";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;
		
		case "CaptainWithCannon_4":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_5", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_5":
			dialog.text = "Eu pensei que você cuidasse dos interesses da tripulação, Alonso. Mas olha só, agora está sugerindo que a gente acorde o próximo turno e levante todo mundo da forma mais bárbara possível?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_6";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_6":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_7", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_7":
			dialog.text = "Me parece sensato animar a tripulação e prepará-los. Não gosto de ficarmos à vista de todos assim. Algo pode acontecer.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_8";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;

		case "CaptainWithCannon_8":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_9", "Quest\Sharlie\Tutorial.c");
		break;

		case "CaptainWithCannon_9":
			dialog.text = "Não zique isso!.. Tá bom. Só uma dose. Branco.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_10";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_10":
			dialog.text = "Divirtam-se, "+pchar.name+". Vamos animar a tripulação... às suas custas, ha ha!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_5");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
		break;
		
		// <-- матрос ругается на ГГ, который активировал пушку
		
		// --> Диалог с матросом, который хочет рома
		case "SailorWantRum":
			dialog.text = "Pode me dar um minuto, monsieur?";
			link.l1 = "Fale, marinheiro.";
			link.l1.go = "SailorWantRum_1";
		break;

		case "SailorWantRum_1":
			dialog.text = "É um prazer conhecê-lo, monsieur. Meu nome é Henry. Interessado em ganhar um dinheiro extra?";
			link.l1 = "Quanto é 'um pouco'?";
			link.l1.go = "SailorWantRum_2";
		break;

		case "SailorWantRum_2":
			dialog.text = "Quinhentos pesos.";
			link.l1 = "Quanto?! O que você quer que eu faça por esse dinheiro todo? Começar um motim?";
			link.l1.go = "SailorWantRum_3";
		break;

		case "SailorWantRum_3":
			dialog.text = "Meu Deus do céu, monsieur! Não precisa gritar!";
			link.l1 = "Isso é muito dinheiro, marinheiro. Você poderia viver muito bem em Paris com isso.";
			link.l1.go = "SailorWantRum_4";
		break;

		case "SailorWantRum_4":
			dialog.text = "Ah, não vou me aproveitar da sua ignorância. Aqui no Caribe, 500 pesos não é nada. Capitães e comerciantes trazem tantas mercadorias que os preços de qualquer coisa minimamente útil vão lá pra cima. Às vezes, uma lâmina rara custa tanto quanto um navio pequeno.";
			link.l1 = "Isso é loucura.";
			link.l1.go = "SailorWantRum_5";
		break;

		case "SailorWantRum_5":
			dialog.text = "O que posso dizer? Estamos todos esperando as coisas se acalmarem e os preços voltarem ao normal. Então, está interessado em ganhar 500 pesos?";
			link.l1 = "Primeiro, quero saber qual é o trabalho.";
			link.l1.go = "SailorWantRum_6";
		break;

		case "SailorWantRum_6":
			dialog.text = "Você certamente está ciente da situação lamentável do rum no navio. Mas estou convencido de que ainda restam algumas garrafas por aí. Rum em garrafa não é a mesma coisa que aquela lavagem de barril. Tem um sabor incrível, evita envenenamento, fortalece o braço e a saúde — um verdadeiro tesouro. Principalmente no fim da viagem, quando o horizonte começa a enlouquecer a gente.";
			link.l1 = "E o que você faria com isso? Por que não procura por conta própria?";
			link.l1.go = "SailorWantRum_7";
		break;

		case "SailorWantRum_7":
			dialog.text = "Quando eu teria tempo? Estamos com pouca gente, então faço o trabalho de três. Quanto ao rum, vou revender — vou encontrar um comprador.";
			link.l1 = "Bem, eu respeito a honestidade em um homem.";
			link.l1.go = "SailorWantRum_8";
		break;
		
		case "SailorWantRum_8":
			dialog.text = "Então, vai aceitar o trabalho? Preciso de três garrafas.";
			link.l1 = "Vou tentar, mas não prometo nada.";
			link.l1.go = "SailorWantRum_9";
			link.l2 = "Prefiro recusar. Esse tipo de trabalho está abaixo de mim.";
			link.l2.go = "SailorWantRum_10";
		break;

		case "SailorWantRum_9":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRum");
		break;

		case "SailorWantRum_10":
			dialog.text = "Uma pena, mas não vou guardar rancor. Tenha uma boa noite, senhor.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
			npchar.SailorWantRum_Done = true;
			DelLandQuestMark(npchar);
		break;

		case "SailorWantRum_PrinestiRum": // ждёт ром
			dialog.text = "Sim, monsieur "+pchar.lastname+"";
			if (GetCharacterItem(pchar, "potionrum") >= 3 && !CheckAttribute(npchar, "questTemp.SailorWantRum_Done"))
			{
				link.l1 = "Aqui estão suas três garrafas de rum.";
				link.l1.go = "SailorWantRum_PrinestiRum_2";
			}
			if (PCharDublonsTotal() >= 42 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Anri"))
			{
				link.l2 = "Henry, tenho algo para você do Monsieur Pinchon.";
				link.l2.go = "RumGold_2";
			}
			link.l3 = "Nada.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "RumGold_2":
			dialog.text = "Sempre feliz em ajudar ele! Quanto é que me devem desta vez?";
			if (PCharDublonsTotal() >= 28)
			{
				link.l1 = "28 dobrões.";
				link.l1.go = "RumGold_DatDeneg_gold28";
			}
			if (PCharDublonsTotal() >= 35)
			{
				link.l2 = "35 dobrões.";
				link.l2.go = "RumGold_DatDeneg_gold35";
			}
			if (PCharDublonsTotal() >= 42)
			{
				link.l3 = "42 doblões.";
				link.l3.go = "RumGold_DatDeneg_gold42";
			}
			// link.l4 = "Preciso conferir tudo de novo. Já volto.";
			// link.l4.go = "RumGold_DatDeneg_3";
		break;

		case "RumGold_DatDeneg_gold28":
			dialog.text = "Obrigado, monsieur "+pchar.lastname+". Mande lembranças ao tesoureiro.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(28);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold35":
			dialog.text = "Obrigado, monsieur "+pchar.lastname+". Mande lembranças ao tesoureiro.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(35);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;

		case "RumGold_DatDeneg_gold42":
			dialog.text = "Obrigado, monsieur "+pchar.lastname+". Mande lembranças ao tesoureiro.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "SailorWantRum_PrinestiRum_2":
			dialog.text = "Obrigado, monsieur "+pchar.lastname+". Isso foi bem feito!";
			link.l1 = "Espero que meu pagamento venha tão tranquilo quanto isso.";
			link.l1.go = "SailorWantRum_PrinestiRum_3";
			RemoveItems(pchar, "potionrum", 3);
			npchar.SailorWantRum_Done = true;
		break;

		case "SailorWantRum_PrinestiRum_3":
			dialog.text = "Você aceitaria um pagamento que não fosse em dinheiro?";
			link.l1 = "Parece que você não é tão honesto quanto diz, não é?";
			link.l1.go = "SailorWantRum_PrinestiRum_4";
		break;

		case "SailorWantRum_PrinestiRum_4":
			dialog.text = "Não, não! Se você quer dinheiro, vai ter dinheiro! Mas eu também posso compartilhar um pouco de conhecimento.";
			link.l1 = "Que tipo de conhecimento?";
			link.l1.go = "SailorWantRum_PrinestiRum_5";
		break;

		case "SailorWantRum_PrinestiRum_5":
			dialog.text = "Posso te contar muita coisa sobre navegação que você não vai encontrar nos seus livros de estudos.";
			link.l1 = "Certo então, me dê a lição mais cara da minha vida.";
			link.l1.go = "SailorWantRum_PrinestiRum_6";
			link.l2 = "Quinhentas dicas não valem quinhentas moedas. Eu fico com o dinheiro.";
			link.l2.go = "SailorWantRum_PrinestiRum_money";
		break;

		case "SailorWantRum_PrinestiRum_money":
			dialog.text = "Aqui está, monsieur "+pchar.lastname+". E obrigado mais uma vez!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
			AddMoneyToCharacter(pchar, 500);
		break;
		
		case "SailorWantRum_PrinestiRum_6":
			dialog.text = "Espero sinceramente que sim, monsieur "+pchar.name+", que minha lição seja útil. Você sabe o que é navegação?";
			link.l1 = "Você pode se surpreender, mas eu sei sim. Eu até sei ler. Navegação é determinar sua posição no espaço e traçar uma rota, por exemplo, para um navio.";
			link.l1.go = "SailorWantRum_PrinestiRum_7";
		break;

		case "SailorWantRum_PrinestiRum_7":
			dialog.text = "Ah. Você quer dizer estrelas e mapas. Não, disso eu não entendo. Isso é coisa do navegador ou do capitão. Aqui, navegação significa saber conduzir e comandar um navio.";
			link.l1 = "Quem está 'por aqui'?";
			link.l1.go = "SailorWantRum_PrinestiRum_8";
		break;

		case "SailorWantRum_PrinestiRum_8":
			dialog.text = "No Caribe. É assim mesmo, não me pergunte por quê. Quanto melhor sua navegação, mais velocidade e manobrabilidade você consegue tirar de um navio. Sua tripulação também lida com as velas mais rápido. Mas isso não é o mais importante.";
			link.l1 = "Você realmente sabe como criar suspense.";
			link.l1.go = "SailorWantRum_PrinestiRum_9";
		break;

		case "SailorWantRum_PrinestiRum_9":
			dialog.text = "Quanto melhor for sua navegação, maior será o navio que você poderá comandar! Se pegar um navio avançado demais, vai perder foco, energia e até saúde!";
			link.l1 = "Parece perigoso. Estranho eu ter sobrevivido tanto tempo sem saber disso.";
			link.l1.go = "SailorWantRum_PrinestiRum_10";
		break;

		case "SailorWantRum_PrinestiRum_10":
			dialog.text = "Por sorte, você não precisa ser especialista em tudo. Sempre pode contratar um bom navegador para compensar suas limitações. Só cuide para que ele esteja bem pago e seja leal. Perder o navegador num navio além das suas habilidades — não é nada divertido.";
			link.l1 = "Valeu pela aula, Henry. Não sei se vou precisar disso, mas acho que conhecimento nunca é demais.";
			link.l1.go = "SailorWantRum_PrinestiRum_11";
			AddCharacterSkillPoints(pchar, "Sailing", 3);
		break;

		case "SailorWantRum_PrinestiRum_11":
			dialog.text = "De nada, monsieur "+pchar.lastname+". E obrigado mais uma vez!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		// <-- Диалог с матросом, который хочет рома
		
		// --> Диалог со старым матросом в трюме
		case "OldSailor":
			dialog.text = "(canta) C’est la mère Michel qui a perdu son chat... Qui crie par la fenêtre à qui le lui rendra...";
			link.l1 = "O que você está fazendo aqui, marinheiro?";
			link.l1.go = "OldSailor_1";
			NextDiag.TempNode = "OldSailor";
		break;
		
		case "OldSailor_1":
			dialog.text = "Então agora estou como Madame Michel — procurando o gato. Só que eu não grito — ela não gosta de gritos.";
			link.l1 = "Vi ela esta manhã — agarrando minhas botas de novo.";
			link.l1.go = "OldSailor_2";
		break;

		case "OldSailor_2":
			dialog.text = "Isso não é nada. As botas do capitão sofreram bem mais. Você gosta de gatos?";
			link.l1 = "É claro que sim.";
			link.l1.go = "OldSailor_3";
			link.l2 = "Na verdade, não.";
			link.l2.go = "OldSailor_4";
		break;

		case "OldSailor_3":
			dialog.text = "Faz sentido. Caso contrário, como lidaríamos com esses malditos ratos?";
			link.l1 = "Mas você não pode depender de gatos para sempre, pode? Eles são criaturas bem teimosas.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "OldSailor_4":
			dialog.text = "Pena. Gatos são queridos e valorizados a bordo. Caso contrário, como lidaríamos com esses malditos ratos?";
			link.l1 = "Mas você não pode depender de gatos para sempre, pode? Eles são criaturas bem voluntariosas.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "OldSailor_5":
			dialog.text = "É verdade. Então, dependemos de arsênico. Só que boa sorte pra achar isso no Caribe. Aí perdemos carga — os ratos estragam o rum, destroem o biscoito e roem o resto\nE o nosso intendente ainda fala: 'Relaxa, é como um imposto de comércio.'\nMas a gente sabe a verdade: ele é só preguiçoso. Se não fosse pela nossa querida Chantal, o capitão já teria mandado ele morar no porão e caçar rato sozinho faz tempo, ha-ha!";
			link.l1 = "Boa sorte com o gato. Preciso ir.";
			link.l1.go = "OldSailor_6";
		break;

		case "OldSailor_6":
			dialog.text = "Espere aí, monsieur. Um marinheiro comum só vê passageiros nobres no convés, mas veja só — você está aqui embaixo, no porão!";
			link.l1 = "A curiosidade matou o gato, ha-ha!";
			link.l1.go = "OldSailor_7";
		break;

		case "OldSailor_7":
			dialog.text = "Interessado em aprender a navegar, é isso?";
			link.l1 = "Parece que cada membro da tripulação está decidido a me transformar em um verdadeiro marinheiro antes de chegarmos em terra.";
			link.l1.go = "OldSailor_8";
		break;

		case "OldSailor_8":
			dialog.text = "Não é de se surpreender. Embora o mar tenha trazido muita tristeza para muitos de nós, amamos o que fazemos. E um marinheiro sempre fica contente quando alguém novo demonstra interesse de verdade.";
			link.l1 = "...";
			link.l1.go = "OldSailor_9";
		break;
		
		case "OldSailor_9":
			dialog.text = "Agora me diga: qual é a habilidade mais importante para um capitão?";
			if (GetSummonSkillFromName(pchar, SKILL_SAILING) >= 6)
			{
				link.l1 = "Navegação. Ela determina o tamanho do navio que ele pode comandar.";
				link.l1.go = "OldSailor_10";
				Notification_Skill(true, 6, SKILL_SAILING);
			}
			else
			{
				link.l1 = "Não vou mentir — não sei.";
				link.l1.go = "OldSailor_9_1";
				Notification_Skill(false, 6, SKILL_SAILING);
			}
		break;

		case "OldSailor_9_1":
			dialog.text = "Não fique chateado, monsieur. Converse com a tripulação, explore o navio. Se descobrir a resposta — vou compartilhar algo realmente fascinante com você. Como se fosse um de nós.";
			link.l1 = "Vou me lembrar disso. Até logo!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OldSailor_again";
		break;

		case "OldSailor_10":
			dialog.text = "Certo! Agora uma mais difícil: velas quadradas ou latinas — quais são melhores?";
			link.l1 = " Difícil dizer, mas sinto que há algum truque nisso. Eu diria que cada um tem seus méritos. ";
			link.l1.go = "OldSailor_11";
		break;

		case "OldSailor_11":
			dialog.text = "Acertou de novo! Velas quadradas são ótimas quando o vento está a favor. Mas um veleiro com velas latinas pode virar e aproveitar até o vento de través. Fico feliz em ver que você não tem desperdiçado seu tempo, monsieur.";
			link.l1 = "Não sei se esse conhecimento vai ser útil algum dia... A não ser que eu queira impressionar as damas da alta sociedade fingindo ser um verdadeiro marinheiro, ha-ha!";
			link.l1.go = "OldSailor_12";
		break;
		
		case "OldSailor_12":
			dialog.text = "Ah, não sei, monsieur "+pchar.name+". Nobre você pode ser — mas nos trata com respeito. Isso a gente valoriza. O capitão está tramando alguma coisa. Um gato preto cruzou o seu caminho.";
			link.l1 = "Besteira. Do que você está falando, marinheiro?";
			link.l1.go = "OldSailor_13";
		break;

		case "OldSailor_13":
			dialog.text = "Dizem que ele mandou uma carta para Capsterville há poucos dias com um navio de passagem\nE acabou à deriva — bem no fim da viagem, quando todos gritavam por terra à vista.";
			link.l1 = "Não ligo para boatos. Pra quê perder tempo? Posso simplesmente perguntar pra ele. Ele não negaria uma resposta direta a um nobre.";
			link.l1.go = "OldSailor_14";
		break;

		case "OldSailor_14":
			dialog.text = "Você não o conhece, monsieur "+pchar.name+". Ele faria — e como. E agora ele está furioso — perdeu sua chave.";
			link.l1 = "Chave?";
			link.l1.go = "OldSailor_15";
		break;

		case "OldSailor_15":
			dialog.text = "No baú dele, na cabine. Acho que está largado por aí.";
			link.l1 = "Achar a chave? Eu?";
			link.l1.go = "OldSailor_16";
		break;

		case "OldSailor_16":
			dialog.text = "Isso depende de você\nAliás, monsieur "+pchar.name+", ainda tem rum? Não me diga que deu tudo pro Henry, ha ha!";
			if (GetCharacterItem(pchar, "potionrum") >= 1)
			{
				link.l1 = "Sim. Aqui está.";
				link.l1.go = "OldSailor_17";
			}
			link.l2 = "Receio que não. Já foi um milagre eu ter encontrado aquelas três garrafas.";
			link.l2.go = "OldSailor_16_1";
		break;

		case "OldSailor_16_1":
			dialog.text = "É verdade. Boa sorte para você, monsieur "+pchar.name+". Vou continuar procurando por aquele canalha listrado.";
			link.l1 = "Boa sorte pra você também, marinheiro.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;
		
		case "OldSailor_17":
			dialog.text = "Você fez um grande favor à tripulação, monsieur "+pchar.name+". Aqui está um amuleto para dar sorte!";
			link.l1 = "Uma pedra com um buraco? Que gracinha.";
			link.l1.go = "OldSailor_18";
			GiveItem2Character(PChar, "talisman11");
			TakeItemFromCharacter(pchar, "potionrum");
		break;

		case "OldSailor_18":
			dialog.text = "Pode rir à vontade. No mar, talismãs não fazem mal nenhum.";
			link.l1 = "Vocês marinheiros são muito supersticiosos. Boa sorte pra vocês.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;

		case "OldSailor_again":
			dialog.text = "Já encontrou a resposta? Qual é a habilidade mais importante para um capitão?";
			if (GetSummonSkillFromName(pchar, SKILL_SAILING) >= 6)
			{
				link.l1 = "Navegação. Isso determina o tamanho do navio que ele pode comandar.";
				link.l1.go = "OldSailor_10";
				Notification_Skill(true, 6, SKILL_SAILING);
			}
			else
			{
				link.l1 = "Ainda não.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OldSailor_again";
				Notification_Skill(false, 6, SKILL_SAILING);
			}
		break;
		
		// <-- Диалог со старым матросом в трюме
		
		// --> Диалог с матросом, которому нужен ящик с ядрами (Поль)
		case "SailorNeedBox":
			dialog.text = "Ei, garoto!";
			link.l1 = "Você não se parece com meu pai. Graças a Deus por isso.";
			link.l1.go = "SailorNeedBox_1";
		break;

		case "SailorNeedBox_1":
			dialog.text = "Ha! Eu teria orgulho de ter um filho tão alto e nobre. Mas só consigo gerar gente simples como eu mesmo.";
			link.l1 = "Certo, vou aceitar o elogio. Qual é o problema?";
			link.l1.go = "SailorNeedBox_2";
		break;

		case "SailorNeedBox_2":
			dialog.text = "Preciso de uma mão aqui, rapaz. Mandaram empilhar munição perto dos canhões — caso a gente tenha problemas nessas águas perigosas. Passei metade do turno puxando essas malditas peças de ferro do porão, e minhas costas não aguentaram a última caixa.";
			link.l1 = "Por que não pergunta logo pros seus colegas? Achei que vocês marinheiros se ajudavam.";
			link.l1.go = "SailorNeedBox_3";
		break;

		case "SailorNeedBox_3":
			dialog.text = "Uma coisa que a nossa irmandade realmente detesta é carregar peso à toa. Hoje fui o azarado — estou arrastando caixas de munição do porão. Trabalho ingrato, indigno de um marinheiro do meu nível. Mas fazer o quê?";
			link.l1 = "Pare de reclamar. Eu vou ajudar. Pelo menos assim vou conhecer essa cela com a qual todo mundo vive me ameaçando.";
			link.l1.go = "SailorNeedBox_4";
			if (IsCharacterPerkOn(pchar, "HT3"))
			{
				link.l2 = "(Atleta) Tá vendo essa espada larga no meu cinto? Ela pesa mais que você. Vou buscar sua bola — não é problema nenhum.";
				link.l2.go = "SailorNeedBox_4";
			}
			link.l3 = "Eu não faço trabalho braçal, marinheiro. Carregue suas próprias caixas.";
			link.l3.go = "SailorNeedBox_Net";
		break;

		case "SailorNeedBox_4":
			dialog.text = "Valeu, garoto. Só não vai acabar se machucando, hein!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBalls");
		break;
		
		case "SailorNeedBox_Net":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "SailorNeedBox_PrinestiBalls":	// ожидание выстрела
			dialog.text = "Como vai, rapaz?";
			if (CheckCharacterItem(PChar, "BoxOfBalls"))
			{
				link.l1 = "Aqui está sua dose. Achei que seriam maiores.";
				link.l1.go = "SailorWantRum_PrinestiBalls_2";
			}
			if (PCharDublonsTotal() >= 30 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Poli"))
			{
				link.l2 = "Seu nome é Paul, certo?";
				link.l2.go = "BallsGold_2";
			}
			link.l3 = "Adeus.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "BallsGold_2":
			dialog.text = "Ah... s-sim.";
			link.l1 = "Seu nome está na lista que o Monsieur Pinchon me deu.";
			link.l1.go = "BallsGold_3";
		break;
		
		case "BallsGold_3":
			dialog.text = "Ufa, por um instante achei que... Sim, Paul - sou eu mesmo. Quanto você trouxe pra mim aí?";
			if (PCharDublonsTotal() >= 20)
			{
				link.l1 = "20 doblões.";
				link.l1.go = "BallsGold_DatDeneg_gold20";
			}
			if (PCharDublonsTotal() >= 25)
			{
				link.l2 = "25 doblões.";
				link.l2.go = "BallsGold_DatDeneg_gold25";
			}
			if (PCharDublonsTotal() >= 30)
			{
				link.l3 = "30 doblões.";
				link.l3.go = "BallsGold_DatDeneg_gold30";
			}
			// link.l4 = "Preciso conferir tudo de novo. Volto mais tarde.";
			// link.l4.go = "BallsGold_DatDeneg_3";
		break;
		
		case "BallsGold_DatDeneg_gold20":
			dialog.text = "Obrigado, rapaz.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(20);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold25":
			dialog.text = "Obrigado, rapaz.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(25);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_gold30":
			dialog.text = "Obrigado, rapaz.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(30);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;

		case "BallsGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "SailorWantRum_PrinestiBalls_2":
			dialog.text = "Se fosse maior, seria um presente para o inimigo! Se acertar o casco — bom, talvez só espirre estilhaços em alguém. Mas se atingir a popa, vai quicar pelo convés inteiro como uma bola!";
			link.l1 = "Já viu isso acontecer antes?";
			link.l1.go = "SailorWantRum_PrinestiBalls_3";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
		break;
		
		case "SailorWantRum_PrinestiBalls_3":
			dialog.text = "Vi com meus próprios olhos, rapaz. O homem é mesmo bom em inventar máquinas de matar. Veja a bala de canhão de uva — alcance curto, não atravessa o casco, mas pode mandar uma dúzia de homens direto pro outro mundo. Ou a bala de corrente — acerta as velas e as transforma em tiras! Quanto às bombas — não digo nada, nunca vi uma, e agradeço a Deus! Ferramentas do diabo, e caras ainda por cima.";
			link.l1 = "Já vi o quão mortais são as balas de canhão — é só perguntar para as suas costas, coitadas.";
			link.l1.go = "SailorWantRum_PrinestiBalls_4";
		break;

		case "SailorWantRum_PrinestiBalls_4":
			dialog.text = "Olha, você me fez um grande favor. E eu vou retribuir. Aqui — uma garrafa quase cheia do melhor rum, ha-ha!";
			link.l1 = "Onde você conseguiu isso? Ouvi dizer que o rum acabou faz tempo. Com esse tipo de mercadoria, você poderia ter feito qualquer um carregar não só uma, mas todas as caixas do porão.";
			link.l1.go = "SailorWantRum_PrinestiBalls_5";
			GiveItem2Character(PChar, "potionrum");
		break;

		case "SailorWantRum_PrinestiBalls_5":
			dialog.text = "Aconteceu assim mesmo, rapaz. Obrigado e até logo.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBallsFinal");
		break;
		
		// <-- Диалог с матросом, которому нужен ящик с ядрами
		
		// --> Диалог с офицером-торговцем, который торгует всяким
		case "OfficerTorgovets":
			dialog.text = "Ah, monsieur "+pchar.lastname+". Se você está pensando em dormir — azar o seu. Nosso artilheiro já tomou sua cama. Como você sabe, acordá-lo não é nada fácil.";
			link.l1 = "Tenho que admitir, quando ele quer — ouve tudo perfeitamente bem!";
			link.l1.go = "OfficerTorgovets_1";
			/*link.l2 = "Não.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets";*/
		break;
		
		case "OfficerTorgovets_1":
			dialog.text = "Isso não é nada. Ouvi dizer que a tripulação do Sharp já teve um artilheiro cego. Diziam que ele mirava pelo som dos canhões.";
			link.l1 = "Você está especialmente falante hoje, monsieur contramestre.";
			link.l1.go = "OfficerTorgovets_2";
		break;

		case "OfficerTorgovets_2":
			dialog.text = "Tem um motivo pra isso! Logo vamos desembarcar — hora de transformar o que sobrou da mercadoria em pesos tilintando. Os bordéis de Saint-Pierre sempre ficam felizes em ver esses, ha-ha!";
			link.l1 = "Engraçado que é você, e não o intendente, quem cuida do pequeno comércio a bordo.";
			link.l1.go = "OfficerTorgovets_3";
		break;

		case "OfficerTorgovets_3":
			dialog.text = "O intendente não sabe conversar com as pessoas! Isso é trabalho do contramestre — ele sim, sabe lidar com palavras e serviço, ha-ha! O intendente tem os próprios esquemas, claro — mas eu não vou me meter nessas águas turvas.";
			link.l1 = "E o que temos de especial hoje?";
			link.l1.go = "OfficerTorgovets_4";
		break;

		case "OfficerTorgovets_4":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Última garrafa de rum no navio, uns amuletos de sorte... e voilà! Um mapa do tesouro completo.";
				link.l1 = "Você devia ser um comerciante, não um contramestre! Vamos ver do que você é capaz.";
				npchar.SharlieTutorial_question_0 = true;
			}
			else
			{
				dialog.text = "Mais alguma coisa?";
				link.l1 = "Vamos ver do que você é capaz.";
			}
			link.l1.go = "OfficerTorgovets_5";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Amuletos? Tipo esse que está pendurado no seu pescoço?";
				link.l2.go = "OfficerTorgovets_6_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Desculpe... você disse um mapa do tesouro?";
				link.l3.go = "OfficerTorgovets_6_question_2_1";
			}
			link.l4 = "Talvez em outra ocasião.";
			link.l4.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_5":
			DialogExit();
			NextDiag.CurrentNode = "OfficerTorgovets_4";
			sld = ItemsFromID("map_full");
			sld.price = 4000;
			LaunchItemsTrade(NPChar, 0);
		break;

		case "OfficerTorgovets_6_question_1_1":
			dialog.text = "Ah, olhos atentos, monsieur. Sim, a 'Cabeça de Coral' — é uma bela peça. Principalmente para mim. Se eu precisar liderar um grupo de abordagem — isso me ajuda a reunir os homens.";
			link.l1 = "Você realmente acredita nisso?";
			link.l1.go = "OfficerTorgovets_6_question_1_2";
		break;

		case "OfficerTorgovets_6_question_1_2":
			dialog.text = "Eu não preciso acreditar. É assim que as coisas funcionam no Caribe, e essa é a vida de marinheiro. Amuletos são coisas úteis. Então, se vai ficar com a gente, recomendo levar alguns — para diferentes ocasiões.";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "OfficerTorgovets_6_question_2_1":
			dialog.text = "Ah, sim. Isso não é raro no Caribe. Alguns têm sorte — ficam ricos de repente. Aí, ou pagam impostos, vivem tranquilos e por muito tempo... ou escondem o ouro numa caverna. E o que sobra é um túmulo, um tesouro... e um pedaço de papel.";
			link.l1 = "Assim mesmo?";
			link.l1.go = "OfficerTorgovets_6_question_2_2";
		break;

		case "OfficerTorgovets_6_question_2_2":
			dialog.text = "Nem tanto. Mapas são caros, e ainda atraem outros caçadores como você. E às vezes o butim mal paga o trabalho. Até o grande Albert Blackwood penou no começo. Faça da caça ao tesouro o seu ofício — quanto mais encontrar, maiores as recompensas. E se tiver um amuleto da sorte — melhor ainda!";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_2 = true;
		break;
		// <-- Диалог с офицером-торговцем, который торгует всяким
		
		// --> Диалог с офицером-казначеем
		case "OfficerKaznachey":
			dialog.text = "Monsieur "+pchar.lastname+"! Só um instante.";
			link.l1 = "De novo com as lições, Monsieur Pinchon? Eu nem encostei na sua tinta preciosa!";
			link.l1.go = "OfficerKaznachey_2";
		break;

		case "OfficerKaznachey_2":
			dialog.text = "Então com o que você está rabiscando no seu livrinho? Água benta? Não havia tinta no inventário dos passageiros. De qualquer forma, você tem problemas maiores agora.";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_3";
		break;

		case "OfficerKaznachey_3":
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) sStr = "And two hundred more — for the broken windlass. The anchor cable snapped.";
			dialog.text = "Você ainda deve trinta pesos ao cofre do navio — pelo barril de chuva que você estragou. Sua tentativa hilária de lavar a camisa teria custado ainda mais se não tivesse chovido de novo bem na hora. "+sStr+"";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass"))
			{
				if (sti(pchar.Money) >= 230)
				{
					link.l1 = "Era só o que me faltava — dívidas logo que desço do navio. Aqui está.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			else
			{
				if (sti(pchar.Money) >= 30)
				{
					link.l1 = "Era só o que me faltava — dívidas assim que desembarquei. Pronto, tá aqui.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			link.l2 = "É só isso? Isso não é dívida de jogo. Estou um pouco ocupado — você vai ter que esperar até chegarmos ao porto.";
			link.l2.go = "OfficerKaznachey_3_1";
		break;

		case "OfficerKaznachey_3_1":
			dialog.text = "Que pena. Muito bem — vamos ao que interessa. Tenho uma tarefa para você.";
			link.l1 = "Você não é exatamente uma pessoa sociável, né?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_4":
			dialog.text = "Um momento, deixe-me contar.";
			link.l1 = "Não se esqueça de contar as migalhas de pão que deixei na mesa depois do jantar.";
			link.l1.go = "OfficerKaznachey_5";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddMoneyToCharacter(pchar, -230);
			else AddMoneyToCharacter(pchar, -30);
		break;
		
		case "OfficerKaznachey_5":
			dialog.text = "Parabéns. O tesouro do navio não tem mais perguntas para você. Por enquanto.\n Indo direto ao assunto — tenho uma tarefa para você.";
			link.l1 = "Você não é exatamente uma pessoa sociável, né?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_6":
			dialog.text = "Pessoas? Nem tanto. Mas eu sou bom com números.\nE você, monsieur "+pchar.lastname+" — você sabe contar?";
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				link.l1 = "(Contador) Não sou nenhum novato em livros-caixa ou letras de câmbio. Até sei o que significa zero.";
				link.l1.go = "OfficerKaznachey_7";
			}
			else
			{
				link.l1 = "O suficiente para esticar a mesada magra do meu pai durante a temporada.";
				link.l1.go = "OfficerKaznachey_8";
			}
		break;

		case "OfficerKaznachey_7":
			dialog.text = "Ooooh! Pena que você não me contou antes – essa viagem poderia ter sido muito mais interessante.";
			link.l1 = "Você mencionou uma tarefa?";
			link.l1.go = "OfficerKaznachey_9";
		break;

		case "OfficerKaznachey_8":
			dialog.text = "Para o seu próprio bem, espero que você nunca se torne dono de um navio. Você iria à falência — e levaria todo mundo junto.";
			link.l1 = "Você mencionou uma tarefa?";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_9":
			dialog.text = "Sim. Não sei se você sabe, mas o intendente e o médico só ficam abaixo do capitão.\n"+"Zarpar sem nenhum dos dois é arriscar seu dinheiro. E sem dinheiro, um navio não passa de um pedaço de madeira muito caro.\n"+"Até mesmo uma pequena escuna pode levar seu capitão à falência sem um intendente. E a primeira batalha sem um médico pode dizimar toda a tripulação — obrigando a um longo e caro processo de contratar e treinar substitutos.\n"+"Por sorte para nós dois, eu faço ambos os papéis. Isso me permite negociar pessoalmente e pedir pequenos favores à tripulação.\n"+"Claro, eu pago muito bem — e agora é uma boa hora pra isso.\n"+"Quero que você pegue esta lista, este baú de dobrões — e pague a tripulação.\n"+"Exatamente como está na lista! Por isso perguntei se você sabia contar.";
			link.l1 = "Por que você mesmo não faz isso? Se eles estão esperando pagamento — que venham até você.";
			link.l1.go = "OfficerKaznachey_10";
		break;
		
		case "OfficerKaznachey_10":
			dialog.text = "Muita coisa pra fazer agora. Faltam só alguns dias pra viagem acabar — e logo vai ter uma fila de cem marinheiros exigindo o pagamento.";
			link.l1 = "Você mencionou dobrões...";
			link.l1.go = "OfficerKaznachey_11";
		break;

		case "OfficerKaznachey_11":
			dialog.text = "Moeda de ouro espanhola. Dinheiro de verdade. A verdadeira medida da riqueza. Só os serviços mais raros e valiosos são pagos com elas.\nElas são guardadas em baús como este, por praticidade.";
			link.l1 = "E o que eu ganho com isso?";
			link.l1.go = "OfficerKaznachey_12";
		break;

		case "OfficerKaznachey_12":
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				dialog.text = "(Contador) 150 pesos, e mais 5 dobrões — por ser praticamente meu colega. E você ainda vai receber uma cotação justa entre pesos e dobrões.";
			}
			else
			{
				dialog.text = "150 pesos, e a possibilidade de trocar pesos por dobrões. Não é muito, mas o trabalho é simples.";
			}
			link.l1 = "Certo. Entregue a lista e o baú.";
			link.l1.go = "OfficerKaznachey_11_agree";
			link.l2 = "Receio que esse tipo de trabalho não seja para mim. Adeus, Monsieur Pinchon.";
			link.l2.go = "OfficerKaznachey_11_otkaz";
		break;
		
		case "OfficerKaznachey_11_otkaz":
			dialog.text = "Sua escolha. Só fique fora do meu caminho, monsieur "+pchar.lastname+"";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
		break;

		case "OfficerKaznachey_11_agree":
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("Chest")].weight) > GetMaxItemsWeight(pchar))
			{
				dialog.text = "Aqui está. Pelo amor de Deus — não esqueça de pegar os dobrões no baú, siga a lista à risca e não fique com nada a mais. Quero o baú vazio de volta também.\nNão se esforce demais, monsieur. Por que está carregando tanta tralha? Recomendo guardar algumas coisas em um baú.";
			}
			else
			{
				dialog.text = "Aqui está. Pelo amor de Deus — não esqueça de pegar os dobrões no baú, siga a lista à risca e não fique com nada a mais. Quero o baú vazio de volta também.";
			}
			link.l1 = "Como quiser. Até logo, Monsieur Pinchon.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_QuestRazdatZoloto");
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "1");
			else AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "2");
			GiveItem2Character(PChar, "chest");
			if (!isMultiObjectKnown("gold_dublon"))
			{
				SetAlchemyRecipeKnown("gold_dublon");
				SetAlchemyRecipeKnown("Chest");
			}
		break;
				
		case "OfficerKaznachey_12_Wait":
			dialog.text = "Como foi? Pagou todo mundo? Pegou os dobrões que sobraram e o baú vazio?";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuest") && sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) == 3 && CheckCharacterItem(PChar, "chest_open") && PCharDublonsTotal() >= 18)
			{
				link.l1 = "Tudo pronto.";
				link.l1.go = "OfficerKaznachey_13";
			}
			link.l2 = "Ainda não, Monsieur Pinchon.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerKaznachey_12_Wait";
		break;

		case "OfficerKaznachey_13":
			dialog.text = "Vamos ver...";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_14";
		break;

		case "OfficerKaznachey_14":
			addGold = PCharDublonsTotal();
			if (addGold >= 18 && addGold <= 39)
			{
				dialog.text = "E você ainda disse que sabia contar. Trouxe menos dobrões do que o esperado. Isso significa mais trabalho para mim, não menos — e isso quer dizer que você não vai receber nada.";
				link.l1 = "Mas você ainda vai trocar dobrões?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold >= 41)
			{
				dialog.text = "E você ainda disse que sabia contar. Trouxe mais do que devia. Isso só me dá mais trabalho, não menos — e isso significa que você não vai receber nada.";
				link.l1 = "E quanto à troca?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold == 40)
			{
				if (IsCharacterPerkOn(pchar, "HT2"))
				{
					dialog.text = "Tudo certo. Bom ver que a geração mais nova ainda sabe contar. Obrigado, monsieur "+pchar.lastname+". Aqui está o seu pagamento — e um pequeno bônus, de um profissional para outro.";
					link.l1 = "E a troca?";
					link.l1.go = "OfficerKaznachey_15_gold_100";
					AddItems(pchar, "gold_dublon", 5);
				}
				else
				{
					dialog.text = "Tudo certo. Fico feliz em ver jovens tratando o dinheiro com responsabilidade. Obrigado, monsieur "+pchar.lastname+". Aqui está o seu pagamento.";
					link.l1 = "Ainda está fazendo trocas?";
					link.l1.go = "OfficerKaznachey_15_gold_105";
				}
				AddMoneyToCharacter(pchar, 300);
				AddCharacterSkillPoints(pchar, "Commerce", 1);
			}
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "chest_open");
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", 100);
			pchar.questTemp.SharlieTutorial_KaznacheyQuestCompleted = true;
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive");
			npchar.Merchant.type = "SharlieTurorialK";
			pchar.SharlieTutorial.FullyCompleted = sti(pchar.SharlieTutorial.FullyCompleted) + 1;
		break;
		
		case "OfficerKaznachey_15_gold_115":
			dialog.text = "Por que não. 115 pesos por dobrão. Procure-me se tiver interesse.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 115;
		break;

		case "OfficerKaznachey_15_gold_105":
			dialog.text = "Claro. 105 pesos por doblão. Se ficar interessado, venha falar comigo.\nDeixe-me te dar um conselho: se o destino algum dia te colocar no comando de um navio, contrate um tesoureiro antes de qualquer coisa. Mesmo um ruim vai te poupar uma fortuna.";
			link.l1 = "Obrigado, Monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 105;
		break;

		case "OfficerKaznachey_15_gold_100":
			dialog.text = "Claro! 100 pesos por doblão — uma taxa justa. Os bancos do Caribe cobrariam ainda mais de você.\nDeixe-me te dar um conselho: se o destino algum dia te colocar no comando de um navio, contrate um tesoureiro antes de qualquer coisa. Mesmo um ruim vai te poupar uma fortuna.";
			link.l1 = "Obrigado, Monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 100;
		break;
		
		case "OfficerKaznachey_16_Proval": // Если не выполнил задание, то отбирает дублоны
			dialog.text = "Vadiando por aí, monsieur "+pchar.lastname+"?";
			link.l1 = "Você também foi mandado para o porão?";
			link.l1.go = "OfficerKaznachey_16_Proval_2";
		break;
		
		case "OfficerKaznachey_16_Proval_2":
			dialog.text = "Eu sou o médico do navio, "+pchar.lastname+"! Logo o camarote estará cheio de feridos, e eu vou ver mais sangue do que qualquer combatente. E mesmo que eu fosse só o intendente, ainda assim enfrentaria o perigo junto com todos. Não, o único que foi mandado descansar no porão aconchegante é você.";
			link.l1 = "Então o que você está fazendo aqui embaixo?";
			link.l1.go = "OfficerKaznachey_16_Proval_3";
		break;
		
		case "OfficerKaznachey_16_Proval_3":
			dialog.text = "A batalha só começa daqui a algumas horas, então é o momento perfeito para fechar as contas do dia. Você está com meu baú de dobrões, de Maure. Por gentileza, devolva-o.";
			if (PCharDublonsTotal() >= 1 || GetCharacterItem(pchar, "chest") >= 1 || GetCharacterItem(pchar, "chest_open") >= 1)
			{
				link.l1 = "Pega. E não apareça mais por aqui.";
				link.l1.go = "OfficerKaznachey_16_Proval_4";
			}
			else
			{
				link.l1 = "Deixei suas coisas em outro lugar.";
				link.l1.go = "OfficerKaznachey_16_Proval_5";
			}
		break;
		
		case "OfficerKaznachey_16_Proval_4":
			addGold = PCharDublonsTotal();
			dialog.text = "Não era minha intenção. Não sou um marinheiro de terra firme – meu lugar não é no porão. Adeus.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			if (PCharDublonsTotal() >= 1 || GetCharacterItem(pchar, "chest") >= 1) ChangeCharacterComplexReputation(pchar, "nobility", -3);
			else ChangeCharacterComplexReputation(pchar, "nobility", -6);
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", addGold);
			TakeItemFromCharacter(pchar, "chest");
			TakeItemFromCharacter(pchar, "chest_open");
		break;
		
		case "OfficerKaznachey_16_Proval_5":
			dialog.text = "Em outro lugar... Vamos discutir isso depois da batalha – na presença do capitão. Até lá.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
		break;
		
		case "TreasurerTrade":
			dialog.text = "Interessado em dobrões, monsieur "+pchar.lastname+"?";
			link.l1 = "Vamos fazer um acordo.";
			link.l1.go = "TreasurerTrade_1";
			link.l2 = "Agora não.";
			link.l2.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
		break;
		
		case "TreasurerTrade_1":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "TreasurerTrade";
		break;
		// <-- Диалог с офицером-казначеем
		
		// --> Матрос сообщает о приближающихся кораблях
		case "Sailor_Trevoga":
			dialog.text = "Capitão, alarme! Piratas no horizonte!";
			link.l1 = "...";
			link.l1.go = "Sailor_Trevoga_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain"));
			PlaySound("Ship\rynda_alarm.wav");
		break;

		case "Sailor_Trevoga_2":
			StartInstantDialog("SharlieTutorial_Captain", "Sailor_Trevoga_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "Sailor_Trevoga_3":
			dialog.text = "Alonso, por favor, acompanhe o Monsieur "+pchar.lastname+" para o porão. E certifique-se de que o Monsieur Drussac esteja acordado e com os artilheiros prontos.";
			link.l1 = "Capitão, estou pronto para lutar! Um nobre não pode...";
			link.l1.go = "Sailor_Trevoga_4_fencing";
			link.l2 = "Se eu puder ajudar de alguma forma...";
			link.l2.go = "Sailor_Trevoga_4_leadership";
			link.l3 = "Espera, isso quer dizer que não vai ter Borgonha?..";
			link.l3.go = "Sailor_Trevoga_4_fortune";
		break;

		case "Sailor_Trevoga_4_fencing":
			dialog.text = "Alonso, tire ele daqui. Andem logo, seus preguiçosos! Icem as velas!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Sailor_Trevoga_4_leadership":
			dialog.text = "Alonso, tire ele daqui. Andem logo, seus preguiçosos! Icem as velas!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Sailor_Trevoga_4_fortune":
			dialog.text = "Alonso, tire ele daqui. Andem logo, seus preguiçosos! Icem as velas!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
				// <-- Матрос сообщает о приближающихся кораблях
				
				// --> Диалог с пиратом в трюме
		case "EnemyPirate_1":
			dialog.text = "Que o diabo leve! Demônios teimosos!";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_2";
			//PlaySound("VOICE\Spanish\OliverTrast01.wav"); //вставить для испанской версии
			PlaySound("interface\abordage.wav");
			PlaySound("interface\abordage.wav");
		break;

		case "EnemyPirate_2":
			dialog.text = "E o que você está fazendo aqui?! Abandonando sua tripulação e se escondendo da luta, seu rato imundo?! Eu vou te abrir agora mesmo!";
			link.l1 = "Má ideia se enfiar no meu porão. Eu mesmo vou te abrir.";
			link.l1.go = "EnemyPirate_3_Fencing";
			link.l2 = "Você mal consegue ficar de pé, e a maior parte desse sangue em você nem é seu.";
			link.l2.go = "EnemyPirate_3_Leadership";
			if (IsCharacterPerkOn(pchar, "HT1"))
			{
				link.l3 = "(Duelista) Como senti falta disso.";
				link.l3.go = "EnemyPirate_3_Duelyant";
			}
		break;

		case "EnemyPirate_3_Fencing":
			dialog.text = "Heh-heh. Vai lá então, almofadinha.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "EnemyPirate_3_Leadership":
			dialog.text = "Heh-heh. Então não tenho nada a perder.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "EnemyPirate_3_Duelyant":
			dialog.text = "O que você está falando?! ";
			link.l1 = "Dois meses. Dois meses tive que manter minha espada embainhada. Vamos dançar!";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "EnemyPirate_4":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_2");
		break;
		
		// <-- Диалог с пиратом в трюме
		
		// --> Диалог с выжившим матросом
		case "SailorAlive_1":
			dialog.text = "Pelo menos você está vivo... Eu estou acabado. Levei uma pancada feia no leme...";
			link.l1 = "O que aconteceu?!";
			link.l1.go = "SailorAlive_2";
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_2":
			dialog.text = "Fomos abordados. Argh! Demônios teimosos!\nEscute bem: seguramos o convés dos canhões, mas a diversão só está começando lá em cima. Juro, eles vão descer aqui a qualquer momento. Pegue a escopeta! Diabo, cuidado! Está carregada!";
			if (IsCharacterPerkOn(pchar, "HT4"))
			{
				link.l1 = "(Atirador de elite) Não se preocupe comigo. Eu faço buraco em quem tentar.";
			}
			else link.l1 = "...";
			link.l1.go = "SailorAlive_3";
		break;

		case "SailorAlive_3":
			dialog.text = "Tem bala de canhão aí. Se fizer direito, dá pra derrubar dois ou três de uma vez.\nEu confio em você, "+pchar.name+". Assim que acabar com eles, dê uma olhada nos corpos. Quem sabe você encontra uma bebida pra mim... caso contrário, não vou poder ajudar.";
			link.l1 = "Aguente firme, Alonso. Lá vêm os convidados!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_5");
			GiveItem2Character(PChar, "pistol3");
			EquipCharacterByItem(PChar, "pistol3");
			AddItems(pchar, "grapeshot", 5);
			AddItems(pchar, "GunPowder", 5);
			LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
		break;

		case "SailorAlive_11":
			dialog.text = "Certo... Bom trabalho, "+pchar.name+". Você encontrou alguma coisa para mim?";
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				link.l1 = "Acho que é isso. Mas parece um pouco suspeito.";
				link.l1.go = "SailorAlive_12";
			}
			link.l2 = "Ainda procurando!";
			link.l2.go = "exit";
			NextDiag.TempNode = "SailorAlive_11";
		break;

		case "SailorAlive_12":
			dialog.text = "Nada mal, ha-ha! Valeu, "+pchar.name+". E aqueles três — você lidou muito bem com eles. Já que você é mesmo um nobre, assuma o comando. Juntos, conseguimos segurar este convés. E se os rapazes lá em cima também derem conta — o dia será nosso!";
			link.l1 = "...";
			//link.l1.go = "exit";
			link.l1.go = "SailorAlive_13";
			//AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_7");
			TakeItemFromCharacter(pchar, "quest_potion");
			PlaySound("Ambient\Tavern\glotok_001.wav");
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_13":
			/*if (CheckAttribute(npchar, "fighter"))
			{
				dialog.text = "Bem melhor. Você carregou a espingarda?";
				link.l1 = "Só fazendo isso... Por que ficou tudo tão silencioso de repente?";
				link.l1.go = "SailorAlive_14";
				SetMusic("");
			}
			else
			{
				dialog.text = "Já que você é mesmo um nobre, assuma o comando.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "SailorAlive_13";
			}*/
			dialog.text = "Bem melhor. Você carregou a espingarda?";
			link.l1 = "Só estou fazendo isso... Por que ficou tão silencioso de repente?";
			link.l1.go = "SailorAlive_14";
			SetMusic("");
			LAi_SetActorType(npchar);
			LAi_ActorSetGroundSitMode(npchar);
			LAi_ActorAnimation(npchar, "ground_standup", "1", -1);
		break;

		case "SailorAlive_14":
			dialog.text = "Só pra dar um toque de drama. Está prestes a começar.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_8");
		break;
		// <-- Диалог с выжившим матросом
		
		// --> Диалог с Алонсо после боя
		case "AfterBattle_Alonso_1":
			dialog.text = "Aqui estamos nós, terminando onde começamos. Obrigado por me salvar a pele, "+pchar.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_Ranen"))
			{
				link.l1 = "Acho que agora estamos quites. Nem lembro direito como você me tirou de lá.";
			}
			else
			{
				link.l1 = "Acho que agora estamos quites. Se não fosse por você e pelos rapazes, eu ainda estaria lá.";
			}
			link.l1.go = "AfterBattle_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "AfterBattle_Alonso_2":
			dialog.text = "Você podia ter ficado no porão, como te mandaram. Pena que o capitão não viveu pra te dar uma bela bronca.";
			link.l1 = "Tivemos que desenterrá-lo debaixo de uma pilha de corpos. Quantos canalhas ele derrubou?";
			link.l1.go = "AfterBattle_Alonso_3";
		break;

		case "AfterBattle_Alonso_3":
			dialog.text = "Alguns dizem que ele derrubou três. Outros juram que foram uma dúzia. Acho que só o diabo sabe ao certo.";
			link.l1 = "Você ainda não me contou como tudo acabou desse jeito.";
			link.l1.go = "AfterBattle_Alonso_4";
		break;

		case "AfterBattle_Alonso_4":
			dialog.text = "O que há pra contar? Nossos canhões de dezesseis libras não nos salvaram de um único brigue pirata.\n"+"Foi em cima da gente num piscar de olhos, disparou metralha enquanto manobrávamos e já veio pra bordo. Você precisava ver o convés — não sobrou nada pro cirurgião fazer.\n"+"O pior de lutar contra piratas — não dá lucro. Só miseráveis. Nem conseguimos ficar com a chalupa deles.";
			link.l1 = "E o que acontece agora?";
			link.l1.go = "AfterBattle_Alonso_5";
		break;

		case "AfterBattle_Alonso_5":
			dialog.text = "O navio está flutuando, e ainda temos tripulação suficiente para levar você a Saint-Pierre no prazo. Lá, vou procurar um novo capitão, e você vai encontrar seu irmão e contar tudo sobre suas aventuras. O que vem depois — só Deus sabe.\n"+"Mas de uma coisa eu tenho certeza – você vai se encaixar muito bem com a gente. Nada mal para um rato de terra, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "AfterBattle_Alonso_6";
		break;

		case "AfterBattle_Alonso_6":
			dialog.text = "Ha! Você está prestes a se revirar por dentro. Não tenha vergonha. Isso é só o medo indo embora do seu corpo. Bem-vindo ao Caribe!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_SeaNearMartinique");
		break;
		
		// <-- Диалог с Алонсо после боя
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}