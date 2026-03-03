void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "O que você precisa?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		case "dwh_gypsy_0":
			dialog.text = "...";
			link.l1 = "Escuta, sobrancelhudo, ouvi dizer que você cura pessoas, até de doenças graves. Isso é verdade?";
			link.l1.go = "dwh_gypsy_1";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_gypsy_1":
			dialog.text = "Verdade, "+GetSexPhrase("querida","beleza")+". Eu tenho meu próprio jeito de lidar com qualquer doença. Já ajudei plebeus, comerciantes, até ricos a se reerguerem. Ora, até o governador recorreu às minhas poções quando ninguém mais pôde ajudar. A doença não teme o ouro, mas não resiste aos meus remédios.";
			link.l1 = "Então por que você se recusa a tratar uma garota gravemente doente, a filha de Thomas Morrison?";
			link.l1.go = "dwh_gypsy_2";
			pchar.questTemp.DWH_gipsy = true;
		break;
		
		case "dwh_gypsy_2":
			dialog.text = "Quem foi que te contou essa bobagem, "+GetSexPhrase("falconet","dovey")+"? Eu não me recusei a ajudar. Foi o pai dela quem me expulsou de casa. Tínhamos combinado que eu cuidaria dela, e de repente ele mudou de ideia. Me botou pra fora como se eu fosse um inimigo declarado.";
			link.l1 = "Então ele condenou a própria filha a sofrer pelas mãos dele mesmo?";
			link.l1.go = "dwh_gypsy_2_1";
		break;
		
		case "dwh_gypsy_2_1":
			dialog.text = "Não, não, ele é um pai atencioso. É difícil imaginar por que ele agiu assim.";
			link.l1 = "Você tentou falar com ele de novo?";
			link.l1.go = "dwh_gypsy_3";
		break;
		
		case "dwh_gypsy_3":
			dialog.text = "Ele nem me deixa chegar perto da casa. Escuta, "+GetSexPhrase("querida","beleza")+", já que você se importa com o destino de uma pobre garota, talvez possa tentar descobrir o que está acontecendo? Fale com Thomas, me ajude a salvar a criança do sofrimento.";
			link.l1 = "Claro que vou ajudar. Onde posso encontrar o Thomas?";
			link.l1.go = "dwh_gypsy_4";
			link.l2 = "Não, sobrancelha cerrada. Seja como for, tenho certeza de que o pai dela tem seus motivos para recusar sua ajuda. Não vou me meter. Deixe que ele decida — ela é filha dele.";
			link.l2.go = "dwh_gypsy_otkaz";
		break;
		
		case "dwh_gypsy_otkaz":
			DialogExit();
			CloseQuestHeader("DWH");
		break;
		
		case "dwh_gypsy_4":
			dialog.text = "A casa deles fica junto ao muro, na parte norte da cidade, ao lado de uma mansão imponente com colunas. Vá lá, "+GetSexPhrase("falconet","dovey")+", fale com ele e volte para mim.";
			link.l1 = "Eu volto logo.";
			link.l1.go = "dwh_gypsy_5";
		break;
		
		case "dwh_gypsy_5":
			DialogExit();
			AddDialogExitQuestFunction("DWH_gypsy_5");
		break;

		case "dwh_gypsy_repeat":
			dialog.text = "Bem, "+GetSexPhrase("querida","querida")+", você já falou com o Thomas?";
			link.l1 = "Ainda não.";
			link.l1.go = "dwh_exit";
		break;

		case "dwh_exit":
			DialogExit();
			NextDiag.TempNode = "dwh_gypsy_repeat";
		break;
		
		case "Tomas":
			dialog.text = ""+TimeGreeting()+"! O que traz você à minha casa?";
			link.l1 = "Meu nome é Capitão "+GetFullName(pchar)+". Vim a pedido da cigana. Ela quer saber por que você recusou a ajuda dela. Você está mesmo em condições de recusar qualquer chance, por menor que seja, de curar sua filha?";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_1":
			dialog.text = "Oh, Capitão... Por favor, entenda, eu tive que recusar, mas não foi por vontade própria. Acredite, eu daria qualquer coisa para que Esther se recuperasse.";
			link.l1 = "O que poderia ter feito você recusar a ajuda de que precisa tão desesperadamente?";
			link.l1.go = "Tomas_2";
		break;

		case "Tomas_2":
			dialog.text = "Veja, nossa família sempre foi muito devota. Depois da morte da minha esposa, Olivia, só me restou a fé para seguir em frente. Quando a cigana ofereceu ajuda, aceitei — qualquer coisa para salvar minha filha. Mas... nosso padre descobriu.";
			link.l1 = "Deixe-me adivinhar: ele é contra esse tipo de serviço?";
			link.l1.go = "Tomas_3";
		break;

		case "Tomas_3":
			dialog.text = "Exatamente isso. Ele me convenceu de que só a oração e a vontade do Senhor podem curar minha filha. E caso eu me desvie desse caminho — buscando a ajuda de uma 'bruxa' — ele me ameaçou com excomunhão da igreja. Você entende? Excomunhão!";
			link.l1 = "Então a saúde da Esther depende só da palavra do padre?";
			link.l1.go = "Tomas_4";
		break;

		case "Tomas_4":
			dialog.text = "Minha filha e eu moramos perto da igreja. A fé é tudo para nós. Se a cigana falhar, vou perder não só minha filha, mas também o pouco que me resta neste mundo. As pessoas vão se afastar, a igreja vai nos rejeitar. Esther e eu vamos ficar completamente sozinhas.";
			link.l1 = "E se o padre desse o consentimento? Você deixaria a cigana tentar então?";
			link.l1.go = "Tomas_5";
		break;

		case "Tomas_5":
			dialog.text = "Sim. Se a igreja abençoou as ações dela... Então eu confiaria nela. Estou pronto para tentar qualquer coisa que possa ajudar.";
			link.l1 = "Entendi. Muito bem, Thomas, vou te ajudar. Vou falar com o seu padre. Talvez eu consiga convencê-lo.";
			link.l1.go = "Tomas_6";
		break;

		case "Tomas_6":
			dialog.text = "Você... você está mesmo disposto a nos ajudar? Capitão, vou rezar pelo seu sucesso. Mas lembre-se... nosso padre é teimoso e cheio de princípios, convencê-lo não será fácil.";
			link.l1 = "Princípios podem ser superados com bons argumentos. Espere por mim, volto já.";
			link.l1.go = "Tomas_7";
		break;

		case "Tomas_7":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Tomas_7");
		break;
		
		case "Tomas_11":
			dialog.text = "...";
			link.l1 = "Thomas, consegui convencer o padre.";
			link.l1.go = "Tomas_12";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_12":
			dialog.text = "Sério? Incrível! Então vamos chamar a cigana o quanto antes.";
			link.l1 = "Com certeza, mas há um detalhe. O padre espera que isso não abale sua fé e conta com seu arrependimento sincero e boas ações. Uma dessas ações pode ser comprar um sino novo para a paróquia.";
			link.l1.go = "Tomas_13";
		break;

		case "Tomas_13":
			dialog.text = "Oh, Capitão... Um sino custa caro. Talvez eu tenha que me desfazer de alguma joia da minha falecida esposa. Mas pela Esther, estou pronto para dar tudo o que tenho—e mais. Claro, vou implorar ao Senhor por perdão. Vou até o ferreiro, faço o pedido e encontro a cigana.\nPor favor, diga ao padre que o sino ficará pronto em breve. Eu o trarei, nem que tenha que cavar até debaixo da terra.";
			link.l1 = "Muito bem, Thomas.";
			link.l1.go = "Tomas_14";
		break;
		
		case "Tomas_14":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Tomas_14");
		break;
		
		case "Tomas_15":
			dialog.text = "...";
			link.l1 = "Contei ao padre o que você disse. Ele não vai mais te impedir, então pode começar.";
			link.l1.go = "Tomas_16";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_16":
			dialog.text = "Muito obrigado, Capitão, por sua ajuda! Por favor, aceite estas cinquenta dobrões. É o mínimo que posso fazer por você, e tudo o que tenho no momento...";
			link.l1 = "Que bobagem! Eu não te ajudei por dinheiro. Então, está tudo pronto para... hmm... o tratamento?";
			link.l1.go = "Tomas_16_1";
			link.l2 = "Bem, se você insiste... Tem mais alguma coisa que eu possa fazer?";
			link.l2.go = "Tomas_16_2";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
		break;

		case "Tomas_16_1":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.DWH_GoodChoice = true;
		break;
		
		case "Tomas_16_2":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddItems(pchar, "gold_dublon", 50);
		break;
		
		case "gypsy_1":
			dialog.text = "Para preparar o remédio que vai devolver a saúde da garota, preciso de mangarosa – uma planta rara que cresce em lugares quase intocados pelo homem. Conheço uma caverna fora da cidade, onde sempre aparecem... marginais. Eles queimam a mangarosa para fumar, sem saber do seu poder. Me ajude, "+GetSexPhrase("falconet","dovey")+", arrume um pouco de mangarosa pra mim, nada vai funcionar sem isso.";
			if (CheckAttribute(pchar, "questTemp.Mangarosa"))
			{
				link.l1 = "Mangarosa? Conheço essa planta.";
				link.l1.go = "gypsy_VD_manga_1";
			}
			else
			{
				link.l1 = "Como é que parece?";
				link.l1.go = "gypsy_VD_no_manga";
			}
		break;

		case "gypsy_VD_no_manga":
			dialog.text = "É uma planta relativamente alta, com folhas recortadas e um cheiro agradável, quase entorpecente. Não tem como confundir com outra.";
			link.l1 = "Certo, vou encontrar essa mangarosa.";
			link.l1.go = "gypsy_2";
		break;

		case "gypsy_VD_manga_1":
			dialog.text = "Você mistura isso com seu tabaco também?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Não, de jeito nenhum! Tem uma curandeira chamada Amelia. Ela usa isso para preparar poções que podem, literalmente, virar sua cabeça do avesso.";
				link.l1.go = "gypsy_VD_manga_1_2";
			}
			else
			{
				link.l1 = "Não, mas já lidei com mangarosa algumas vezes.";
				link.l1.go = "gypsy_VD_manga_2";
			}
		break;

		case "gypsy_VD_manga_1_2":
			dialog.text = "Então você conhece a Amelia? Bem, "+GetSexPhrase("falconet","dovey")+", logo você vai estar me dando uma boa competição. Mas agora não é hora pra isso. Vá buscar a mangarosa, e eu vou preparar tudo.";
			link.l1 = "Estou indo.";
			link.l1.go = "gypsy_2";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;

		case "gypsy_VD_manga_2":
			dialog.text = "Entendi, você não é uma pessoa comum, "+GetSexPhrase("falconet","dovey")+". Seu conhecimento é vasto, sua mente afiada como uma lâmina! Você não tem medo de se aventurar pelo desconhecido, está sempre pronto para agarrar o que os outros evitam. Thomas tem sorte de contar com sua ajuda. Agora vá, traga a mangarosa para mim, e eu vou curar a garota.";
			link.l1 = "...";
			link.l1.go = "gypsy_2";
		break;
		
		case "gypsy_2":
			DialogExit();
			AddDialogExitQuestFunction("DWH_gypsy_22");
		break;
		
		case "Bandit_1":
			dialog.text = "Ha-ha. Tô te falando, Mark, ele é um idiota. Nem tranca a própria casa.";
			link.l1 = "Tem certeza de que a galinha dele não vai ficar em casa?";
			link.l1.go = "Bandit_2";
			
			locCameraSleep(true);
			sld = CharacterFromID("DWH_Bandit_1");
			CharacterTurnToLoc(sld, "goto", "ass4");
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "ass2");
		break;
		
		case "Bandit_2":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Bandit_2");
		break;
		
		case "Bandit_3":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Ora, ora, olha só quem caiu na nossa rede! Vamos lá, não fica parado aí. Vira os bolsos, depressa, antes que a gente perca o bom humor.";
			link.l1 = "Calma aí, bandidos. Estou aqui a trabalho. "+sld.name+" me enviou. Preciso de mangarosa.";
			link.l1.go = "Bandit_4";

			locCameraSleep(false);
			locCameraFromToPos(3.39, 1.16, -1.80, true, 3.62, -0.50, 3.63);
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "goto2");
		break;

		case "Bandit_4":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Você diz "+sld.name+" mandou você? Tudo bem, temos mangarosa. Dê-nos dez moedas de ouro e é sua.";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "Aqui está.";
				link.l1.go = "Bandit_5";
			}
			link.l2 = "Dinheiro? Pra quê? Não sou de dar esmola. Mas posso te entregar dois quilos de aço, se preferir!";
			link.l2.go = "Bandit_7";
		break;

		case "Bandit_5":
			dialog.text = "Certo, aqui está sua mangarosa. E lembre-se, você nunca nos viu.";
			link.l1 = "Heh. Não precisava do aviso.";
			link.l1.go = "Bandit_6";
			GiveItem2Character(PChar, "cannabis7");
			RemoveDublonsFromPCharTotal(10);
		break;
		
		case "Bandit_6":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Bandit_6");
		break;
		
		case "Bandit_7":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Bandit_7");
		break;
		
		case "gypsy_3":
			if (CheckCharacterItem(PChar, "cannabis7"))
			{
				dialog.text = "...";
				link.l1 = "Dá uma olhada, "+npchar.name+", é esta a planta que você precisa?";
				link.l1.go = "gypsy_4";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Você trouxe o que eu pedi?";
				link.l1 = "Ainda não, estou trabalhando nisso.";
				link.l1.go = "exit";
				NextDiag.TempNode = "gypsy_3";
			}
		break;

		case "gypsy_4":
			dialog.text = "Sim, é isso. Agora tenho tudo o que preciso, e posso começar.";
			link.l1 = "...";
			link.l1.go = "gypsy_5";
			TakeItemFromCharacter(pchar, "cannabis7");
		break;

		case "gypsy_5":
			StartInstantDialog("DWH_Tomas", "Tomas_17", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
		break;

		case "Tomas_17":
			dialog.text = "Vamos rápido, não podemos perder tempo.";
			link.l1 = "...";
			link.l1.go = "Tomas_18";
			CharacterTurnByChr(npchar, CharacterFromID("DWH_gypsy"));
		break;

		case "Tomas_18":
			dialog.text = "Capitão, se não se importar, conversamos depois. Agora enfrentamos a parte mais crucial... o tratamento.";
			link.l1 = "Claro, Thomas. Espero que sua filha se recupere logo.";
			link.l1.go = "Tomas_19";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tomas_19":
			DialogExit();
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "gypsy_6":	// если не прошли проверку ВД у священника
			dialog.text = "...";
			link.l1 = ""+npchar.name+", Thomas não te afastou por vontade própria. O padre o ameaçou com excomunhão se ele aceitasse a sua ajuda.";
			link.l1.go = "gypsy_7";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_7":
			dialog.text = "Eu percebi na hora, "+GetSexPhrase("querida","beleza")+", que ele me deu aquela recusa com o coração pesado.";
			link.l1 = "Existe alguma maneira de ajudá-lo sem que a igreja se ofenda?";
			link.l1.go = "gypsy_8";
		break;

		case "gypsy_8":
			dialog.text = "Oh, "+GetSexPhrase("querida","beleza")+", não é nada fácil, mas conheço os caminhos, sei o que fazer. Só que, sem a sua ajuda, não consigo, entende.";
			link.l1 = "Claro, pode contar comigo.";
			link.l1.go = "gypsy_10";
			link.l2 = "Me desculpe, sobrancelhudo, mas eu realmente não tenho tempo pra isso. Já fiz tudo que estava ao meu alcance. Agora preciso cuidar dos meus próprios assuntos.";
			link.l2.go = "gypsy_9";
		break;
		
		case "gypsy_9":
			DialogExit();
			CloseQuestHeader("DWH");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("DWH_Tomas");
			sld.lifeday = 0;
		break;
		
		case "gypsy_10":
			dialog.text = "Então aqui está o que eu preciso: um objeto que pertença à moça, dois talos de datura, um talo de ipeca e um de verbena. Se você me trouxer tudo isso, posso preparar uma poção de cura para ela.";
			link.l1 = "Muito bem, vou providenciar tudo o que for necessário.";
			link.l1.go = "gypsy_11";
		break;

		
		case "gypsy_11":
			DialogExit();
			AddQuestRecord("DWH", "7");
			
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_21":
			dialog.text = "...";
			link.l1 = "Thomas, infelizmente, o padre não me ouviu. Mas a cigana e eu podemos te ajudar. Eu preciso...";
			link.l1.go = "Tomas_22";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_22":
			dialog.text = "Você está sugerindo que eu vá contra a igreja?";
			link.l1 = "Vamos fazer tudo discretamente, ninguém vai saber. Logo sua filha poderá aproveitar a vida de novo e andar livremente pela cidade, como uma jovem deve fazer.";
			link.l1.go = "Tomas_23";
			link.l2 = "Droga, Thomas Morrison, você quer mesmo que sua filha melhore ou só está se escondendo atrás de palavras bonitas?";
			link.l2.go = "Tomas_24";
		break;

		case "Tomas_23":
			dialog.text = "Está bem, eu concordo. Mas, por favor, aja com cuidado. Não quero rumores desnecessários nem problemas.";
			link.l1 = "Com certeza. Então, preciso de um objeto pessoal da sua filha. Algo ao qual ela tenha apego.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;

		case "Tomas_24":
			dialog.text = "Está bem, eu concordo. Mas, por favor, aja com cuidado. Não quero rumores desnecessários nem problemas.";
			link.l1 = "Com certeza. Então, preciso de um objeto pessoal da sua filha. Algo ao qual ela tenha apego.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Tomas_25":
			dialog.text = "Hum... Já sei! Eu sei o que vai funcionar. Espere aqui por mim, já volto.";
			link.l1 = "Eu vou esperar...";
			link.l1.go = "Tomas_26";
		break;

		case "Tomas_26":
			DialogExit();
			SetLaunchFrameFormParam("A few minutes later...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("DWH_TomasGovotitAgain", 0.0);
			LaunchFrameForm();
		break;
		
		case "Tomas_27":
			dialog.text = "Aqui. Estas são contas de jade. Esther nunca tirava elas, são muito preciosas para ela.";
			link.l1 = "Excelente. Agora, é só esperar. Até logo, Thomas.";
			link.l1.go = "Tomas_28";
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "Tomas_28":
			DialogExit();
			AddQuestRecord("DWH", "8");

			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "gypsy_21":
			dialog.text = "Você conseguiu tudo o que precisava?";
			if (GetCharacterItem(pchar, "cannabis1") >= 2 && GetCharacterItem(pchar, "cannabis4") >= 1 && GetCharacterItem(pchar, "cannabis3") >= 1)
			{
				link.l1 = "Consegui tudo o que precisava.";
				link.l1.go = "gypsy_22";
			}
			link.l2 = "Me lembra o que eu preciso levar.";
			link.l2.go = "gypsy_napomni";
		break;

		case "gypsy_napomni":
			dialog.text = "Então é o seguinte: preciso de um objeto que pertença à moça, dois ramos de datura, dois de ipeca e um de verbena. Se você trouxer tudo isso, posso preparar uma infusão de ervas para ela.";
			link.l1 = "Muito bem, vou providenciar tudo o que for necessário.";
			link.l1.go = "gypsy_napomni_2";
		break;

		case "gypsy_napomni_2":
			DialogExit();
			NextDiag.TempNode = "gypsy_21";
		break;

		case "gypsy_22":
			dialog.text = "Excelente. Agora posso preparar uma poção de cura para a garota. Ela só ficará pronta amanhã de manhã, no mínimo. Você pode me encontrar como sempre, pelas ruas da cidade.";
			link.l1 = "Muito bem, até logo então.";
			link.l1.go = "gypsy_23";
			DelLandQuestMark(npchar);
			RemoveItems(pchar, "cannabis1", 2);
			RemoveItems(pchar, "cannabis4", 1);
			RemoveItems(pchar, "cannabis3", 1);
			RemoveItems(pchar, "jewelry49", 1);
		break;
		
		case "gypsy_23":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("DWH", "11");
			SetTimerFunction("DWH_GypsyPrigotovilaZelie", 0, 0, 1);
		break;
		
		case "gypsy_31":
			dialog.text = "...";
			link.l1 = "Bem, "+npchar.name+", a sua poção está pronta?";
			link.l1.go = "gypsy_32";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_32":
			dialog.text = "Aí está, "+GetSexPhrase("querida","beleza")+". Deixe a moça colocar essas contas e beber o conteúdo do frasco até o fim. Em no máximo um mês, ela estará completamente saudável.";
			link.l1 = "Vou levar isso para o Thomas imediatamente. Adeus, sobrancelha cerrada.";
			link.l1.go = "gypsy_33";
			GiveItem2Character(PChar, "quest_potion");
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "gypsy_33":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "Tomas_31":
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				dialog.text = "...";
				link.l1 = "Thomas, está tudo pronto. Esther deve colocar essas contas e tomar o conteúdo do frasco de uma vez só.";
				link.l1.go = "Tomas_32";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Tomas_31";
			}
		break;

		case "Tomas_32":
			dialog.text = "Obrigado, "+pchar.name+"! Por favor, me perdoe, não quero perder nem um minuto...";
			link.l1 = "Claro, claro.";
			link.l1.go = "Tomas_33";
			TakeItemFromCharacter(pchar, "quest_potion");
		break;
		
		case "Tomas_33":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "Tomas_41":
			dialog.text = "Saudações, "+pchar.name+"! Minha Esther se recuperou! Ela está completamente saudável e agora está na igreja, agradecendo ao nosso Senhor Deus por ter enviado você e a cigana para nós!";
			link.l1 = "Thomas, fico muito feliz que tudo tenha dado certo! Cuide bem da garota, agora ela tem uma vida longa e feliz pela frente.";
			link.l1.go = "Tomas_42";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_42":
			dialog.text = "Pegue estes trezentos doblões. Infelizmente, não posso oferecer mais, pois precisei me endividar para juntar essa quantia. Mas saiba que nem palavras nem ouro podem expressar a gratidão que sinto por você, Capitão. Você não só me livrou do medo pela vida dela, como também devolveu à nossa família a esperança no futuro. Sempre serei seu devedor!";
			link.l1 = "Obrigado! Trezentos dobrões é uma quantia bem generosa, então fique tranquilo – você já me agradeceu mais do que o suficiente!";
			link.l1.go = "Tomas_43";
			link.l2 = "Não vou aceitar seu dinheiro, Thomas. Nem pense em insistir! É melhor comprar um vestido bonito para a Esther, ela merece.";
			link.l2.go = "Tomas_46";
		break;

		case "Tomas_43":
			dialog.text = ""+pchar.name+", venha nos visitar quando quiser. Você será sempre bem-vindo em nossa casa. Ah, e fale também com a cigana, ela queria te ver.";
			link.l1 = "Vai ser uma honra! Agora preciso partir – as marés não esperam por nenhum capitão.";
			link.l1.go = "Tomas_44";
			AddItems(pchar, "gold_dublon", 300);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "Tomas_44":
			dialog.text = "Claro, claro. Que Deus esteja com você, "+GetFullName(pchar)+"!";
			link.l1 = "Adeus.";
			link.l1.go = "Tomas_45";
		break;
		
		case "Tomas_45":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_41";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_46":
			dialog.text = "Você é uma pessoa realmente nobre, "+GetFullName(pchar)+"! Que a Virgem Maria esteja com você! Venha nos visitar, você é sempre bem-vindo em nossa casa. E também, "+pchar.name+", fale com a cigana, ela queria te ver.";
			link.l1 = "Com certeza! Agora preciso ir - o mar me chama.";
			link.l1.go = "Tomas_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Tomas_47":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_44";
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.DWH_QuestCompleted = true;
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1;
			
			AddSimpleRumourCity("Have you heard? "+GetFullName(pchar)+" procured a remedy for Thomas Morrison's daughter that miraculously restored the poor girl's health!", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Thomas Morrison lights a candle in the parish daily for the health of "+GetFullName(pchar)+". They say thanks to his (her) efforts, Thomas's daughter was freed from a prolonged illness.", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Esther Morrison has blossomed before our eyes. As if she had never been ill. No one can really explain what made the illness retreat.", "SentJons", 10, 1, "");
		break;
		
		case "gypsy_41":
			dialog.text = "E aí está você, "+GetSexPhrase("falconet","dovey")+"! Eu sabia que você voltaria. Graças aos seus esforços, a garota se recuperou e agora anda leve como uma pomba. A cidade inteira fala dela com admiração.";
			link.l1 = "Bem, sobrancelhuda, não fui só eu – não me dê tanto crédito assim. Foi o seu remédio que devolveu a saúde dela, então não menospreze o que você fez.";
			link.l1.go = "gypsy_42";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_42":
			dialog.text = "Você tem um coração bondoso, "+GetSexPhrase("falconet","dovey")+", e uma mente afiada! Você está destinado à grandeza – essa é a minha profecia.";
			link.l1 = "Heh... bem, obrigado, "+npchar.name+".";
			link.l1.go = "gypsy_43";
		break;
		
		case "gypsy_43": // плохой вариант
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "9");
			CloseQuestHeader("DWH");
		break;
		
		case "gypsy_44":
			dialog.text = "E aí está você, "+GetSexPhrase("falconet","dovey")+"! Eu sabia que você apareceria aqui de novo. Graças aos seus esforços, a garota se recuperou e agora está leve como uma pomba. A cidade inteira a admira.";
			link.l1 = "Ora, ora, foi você quem salvou a moça, e agora quer que eu fique com todo o mérito? Assim não dá! Você preparou a poção, você a colocou de pé de novo, é você quem merece os louros.";
			link.l1.go = "gypsy_45";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_45":
			dialog.text = "Você tem um bom coração, "+GetSexPhrase("falconet","dovey")+", e uma alma nobre. Tenho um presente para você – um que qualquer capitão saberia valorizar. Aqui está. Agora, os ratos do seu navio não terão mais felicidade nem sossego!";
			link.l1 = "Um presente para mim? Pelas estrelas, que surpresa inesperada!";
			link.l1.go = "gypsy_46";
			GiveItem2Character(PChar, "rat_poison");
		break;

		case "gypsy_46":
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				dialog.text = "Sua alma é pura, vejo que você não vai queimar mangarosa por um prazer passageiro. Se precisar dela com urgência, venha até mim, "+GetSexPhrase("falconet","dovey")+". Três ramos vão te custar trezentos e cinquenta dobrões\nEssa erva é difícil, nem todo mundo consegue encontrar. Então não me apresse – não peça mais de uma vez por mês, de qualquer jeito não vou conseguir conseguir mais.";
			}
			else
			{
				dialog.text = "Sua alma é luminosa, vejo que você não é tolo, entende de ervas tão bem quanto alguns curandeiros. Você consegue encontrar muitas coisas, embora a sorte nem sempre sorria. Existe uma planta rara que poucos conseguem achar. Chama-se mangarosa. Se algum dia precisar dela, venha até mim, "+GetSexPhrase("falconet","dovey")+". Vou conseguir três ramos, mas não vou dar de graça – vou cobrar trezentos e cinquenta dobrões\nMas essa erva é teimosa, então não me apresse. Não peça mais de uma vez por mês – mesmo que jogue todas as cartas do destino, não vou conseguir antes disso.";
			}
			link.l1 = "Bem, obrigado, "+npchar.name+".";
			link.l1.go = "gypsy_47";
		break;
		
		case "gypsy_47": // хороший вариант
			DialogExit();
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "10");
			CloseQuestHeader("DWH");
			AddQuestRecordInfo("Useful_Acquaintances", "1");
			
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
		
		case "Tomas_51":
			dialog.text = "Capitão, fico pensando – só pode ter sido o próprio Senhor que te trouxe aqui na hora certa! Você salvou minha filha, e eu nunca vou esquecer isso.";
			link.l1 = "Talvez, Thomas. Os caminhos do Senhor são insondáveis.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tomas_52";
			SetTimerFunction("DWH_Tomas_HelloAgain", 0, 0, 1);
		break;

		case "Tomas_52":
			dialog.text = "Gostaria de um pouco de vinho, Capitão? Tenho algo especial para hóspedes queridos.";
			link.l1 = "Obrigado, Thomas, mas infelizmente, eu preciso ir.";
			link.l1.go = "exit";
		break;

		case "gypsy_Mangarosa":
			dialog.text = "O que você precisa, meu falcão?";
			if (CheckAttribute(pchar, "questTemp.DWH_Mangarosa"))
			{
				link.l1 = "Me diga, sobrancelhudo, você teria mangarosa pra mim?";
				link.l1.go = "gypsy_Mangarosa_1";
			}
			link.l2 = "Só passei para dar um oi. Hora de ir embora!";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;
		
		case "gypsy_Mangarosa_1":
			dialog.text = "Quem mais além de mim, "+GetSexPhrase("querida","beleza")+", conseguiria algo tão raro para você? Trezentos e cinquenta dobrões – e é seu, três hastes, nem mais, nem menos.";
			if (PCharDublonsTotal() >= 350)
			{
				link.l1 = "Seu preço é justo. O ouro é seu.";
				link.l1.go = "gypsy_Mangarosa_2";
			}
			link.l2 = "Droga! Minha bolsa está leve demais. Voltarei quando a sorte sorrir para mim.";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;

		case "gypsy_Mangarosa_2":
			dialog.text = "Assim está melhor. Pegue. E cuidado para não desperdiçar à toa, viu – mangarosa não é uma erva comum, há um poder nela que nem todo mundo consegue lidar.";
			link.l1 = "Não se preocupe, sobrancelha cerrada, vou encontrar um bom uso para esse poder.";
			link.l1.go = "gypsy_Mangarosa_3";
			AddItems(pchar, "cannabis7", 3);
			RemoveDublonsFromPCharTotal(350);
		break;
		
		case "gypsy_Mangarosa_3":
			DialogExit();
			
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			DeleteAttribute(pchar, "questTemp.DWH_Mangarosa");
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
	}
}