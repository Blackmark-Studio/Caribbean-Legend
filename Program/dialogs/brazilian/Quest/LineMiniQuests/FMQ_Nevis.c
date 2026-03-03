// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Um bug óbvio. Avise os desenvolvedores sobre isso.";
			link.l1 = "Ah, eu vou.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "seafox":
			DelMapQuestMarkCity("Charles");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_01.wav");
			dialog.text = TimeGreeting()+", capitão. (faz uma continência) Permita-me apresentar - Tenente "+GetFullName(npchar)+", Regimento de Infantaria Marítima de Antígua, guarnecido em St. John's. Tenho um favor a pedir.";
			link.l1 = "Saudações, Tenente Gretton. Meu nome é "+GetFullName(pchar)+". Que tipo de favor?";
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = "Deixe-me explicar rapidamente a situação. Eu e mais quatro dos meus homens estávamos navegando de St. Johns para Sint Maarten quando uma tempestade atingiu nosso navio. O mau tempo não durou muito, mas foi o suficiente para que nosso velho barco começasse a fazer água. Tivemos que mudar o rumo e parar aqui para consertos. Isso está tomando um tempo que não temos\nEstamos com pressa para chegar a Sint Maarten, especificamente à praia de Grand Case. Me ajude, capitão, e eu vou garantir que valha muito a pena para você. Dois dias de viagem por uma recompensa generosa!";
			link.l1 = "Tem que ser um pagamento bem generoso mesmo, tenente, se você quer que eu infiltre fuzileiros ingleses numa ilha holandesa de forma clandestina.";
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = ""+UpperFirst(GetAddress_Form(PChar))+", isso não diz respeito a você. Não corre perigo nenhum. Só nos deixe na baía, e pronto. Então, temos um acordo?";
			link.l1 = "Tá bom, eu topo. Não é tão longe daqui. Me fala desse pagamento.";
			link.l1.go = "seafox_3";
			link.l2 = "Me desculpe, mas tenho assuntos urgentes em outra direção e prefiro não irritar os holandeses.";
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = "Como quiser, capitão. Vou continuar procurando então. Adeus e boa sorte!";
			link.l1 = "Adeus, tenente.";
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info("You have received a purse of doubloons");
			dialog.text = "Dez mil peças de oito. Aqui está um adiantamento.";
			link.l1 = "Ótimo. Leve seus homens a bordo, não vamos perder tempo.";
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = "Sim, senhor capitão!";
			link.l1 = "...";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
			
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_seafox_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "", "", "", "", 10.0); // англичане на борт
			sld.location = "None";
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.FMQN_sailing.win_condition.l1 = "location";
			pchar.quest.FMQN_sailing.win_condition.l1.location = "Shore40";
			pchar.quest.FMQN_sailing.win_condition.l2 = "Ship_location";
			pchar.quest.FMQN_sailing.win_condition.l2.location = "Shore40";
			pchar.quest.FMQN_sailing.function = "FMQN_ArriveMaarten";
			if(bImCasual)
			{
				NewGameTip(StringFromKey("FMQ_69"));
			}
			else SetFunctionTimerCondition("FMQN_SailingLate", 0, 0, 10, false);
			for(i = 0; i < MAX_LOCATIONS; i++)
			{	
				sld = &Locations[i];
				if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
				{
					sld.DisableEncounters = true;	
				}
			}
			sld = &Locations[FindLocation("Shore40")];
			sld.QuestlockWeather = "23 Hour";
			AddMapQuestMarkShore("Shore40", true);
		break;
		
		case "seafox_6":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Obrigado pela viagem tranquila, capitão! Me desculpe mesmo, mas não posso te pagar neste exato momento... Era pra ter um dos nossos luggers por aqui, mas ele não está. Como você pode ver. Preciso pedir sua ajuda mais uma vez. Você poderia esperar nesta baía por dois ou três dias? Temos que dar uma olhada por aí. Assim que voltarmos, leve a gente para Antígua. O coronel Fox vai te recompensar muito bem.";
			link.l1 = "Hmm... Isso não é exatamente o que combinamos...";
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = "Por favor, não fique frustrado, capitão. Eu entendo como deve se sentir, mas infelizmente: estou completamente sem dinheiro. Posso garantir que você será recompensado pelas duas viagens e por ter nos esperado aqui, além de receber os agradecimentos do próprio Coronel Fox!";
			link.l1 = "Não posso simplesmente te deixar na mão... Muito bem, Tenente Gretton. Vou esperar por três dias, mas não mais que isso.";
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = "Obrigado, "+GetAddress_Form(NPChar)+"! Estamos indo para o interior. Juro que estaremos de volta em 72 horas, nem um minuto a mais.";
			link.l1 = "Boa sorte, tenente. Não se deixe pegar.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Que encontro inesperado! Achei que você estaria nos esperando na Praia de Grand Case, Capitão "+pchar.lastname+"!";
			link.l1 = "Olá, Tenente, a surpresa é mútua. Não esperava te ver vestido como um soldado holandês.";
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = "É o nosso disfarce... Por que você está aqui fora, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Esse disfarce é perigoso, camarada. Espiões costumam ser executados sumariamente, sem julgamento. E por falar em execução, se quiser evitar a sua, é melhor prestar atenção.";
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = "Você tem toda a minha atenção.";
			link.l1 = "Eu naveguei até Philipsburg e conversei com os locais depois que você desembarcou. Os holandeses estão de olho em você. Eles já sabem da sua missão para resgatar aqueles oficiais ingleses de alta patente que foram capturados.";
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = "Maldição! Como diabos eles descobriram isso?";
			link.l1 = "Um dos oficiais ingleses capturados. Em troca da liberdade, ele contou aos holandeses tudo o que sabia sobre a operação de resgate. Toda Philipsburg está preparada para você e seus homens tentarem entrar na cidade. Para piorar, uma corveta holandesa está patrulhando o mar ao redor de Sint Maarten. É uma armadilha, tenente.";
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+"Aquele canalha desonrado! Vou descobrir quem é esse traidor e denunciá-lo ao Parlamento!";
			link.l1 = "Isso vai ter que esperar, Sr. Gretton. Volte para Grand Case Beach hoje à noite e retorne ao meu navio antes que te peguem.";
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = "E abandonar cavalheiros ingleses dentro de uma prisão holandesa? Prefiro morrer, senhor. Não vou decepcionar o Coronel Fox.";
			link.l1 = "Hm, você acha que os holandeses vão te deixar escolher entre a forca ou o pelotão de fuzilamento quando te pegarem?";
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = "Não pense que vão simplesmente deixar você zarpar daqui também, Capitão de Maure. Nós dois estamos enfiados até o pescoço nessa história.";
			link.l1 = "Droga, você provavelmente está certo. Aquela corveta vai cair em cima da gente assim que levantarmos âncora...";
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = "Os holandeses podem saber que estamos chegando, mas não sabem *como* vamos chegar. Já cuidamos do disfarce – olha só este uniforme. Bonito, não é? Se nosso plano não tivesse sido traído, iríamos direto à prisão local, pegaríamos todos de surpresa e mataríamos todo mundo lá dentro. Mas com certeza estão esperando por nós em emboscada. Então, vamos improvisar. Capitão, vá até a igreja de Philipsburg e procure um pregador chamado Filippe Jacobsen. Ele deve estar lá das seis às dez da manhã. Filippe é um dos nossos homens infiltrados. Diga a ele esta senha: 'Há quanto tempo os marinheiros cativos se confessaram?'. Depois, explique a situação e exija a ajuda dele em nome do Coronel Fox. Em seguida, traga a resposta dele para mim. Simples, e sem risco para você.";
			link.l1 = "Parece bem arriscado perguntar sobre confissão numa igreja calvinista holandesa, tenente. O pastor ia querer me enforcar por ser papista. Certo, me fale desses uniformes... você pegou isso de uma patrulha holandesa?";
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = "Sim, senhor.";
			link.l1 = "E onde eles estão agora?";
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = "Mantido refém nos arbustos não muito longe desta caverna.";
			link.l1 = "Entendido. Proteja-os, vou até a cidade. Espere por mim aqui e fique quieto – os holandeses estão vasculhando a selva e o mar atrás de você.";
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = "Vamos ser mais quietos que ratos de igreja, capitão. Por favor, seja rápido!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("Voice\English\soldier_common_4.wav");
			DelLandQuestMark(npchar);
			dialog.text = "Você voltou? Capitão, o que está fazendo aqui? Vá para a cidade, você está chamando atenção para nosso esconderijo!";
			link.l1 = "Voltei da cidade. Que tipo de joguinhos vocês, ingleses, estão aprontando?";
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = "Como é que é?";
			link.l1 = "Fui até a igreja. Prédio grande, bonito e austero, do jeito que esses iconoclastas holandeses gostam. Sabe de uma coisa, tenente? Não existe nenhum pregador chamado Filippe Jacobsen.";
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = "Isso é impossível, ele vai lá todas as manhãs-";
			link.l1 = "Cala a boca e me escuta! Se esse tal de Jacobsen realmente existe, ele não vai à igreja! Ninguém nunca viu ele lá! Nem de manhã, nem à noite! Maldição, porra! Por que diabos eu aceitei essa merda de trabalho?! Liderado por um imbecil de merda, um tenente novato, idiota e inexperiente—";
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = "Senhor, exijo satisfação por essa ofensa. Assim que sairmos daqui, vamos duelar conforme os costumes de-";
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = "Cala a boca, todos vocês!!! ... Acabei de ouvir alguma coisa.";
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			if (pchar.sex == "man") {PlaySound("VOICE\English\LE\SeaFox\SeaFox_04.wav");}
			dialog.text = "Maldição, tem alguém lá fora! Você! Você trouxe os holandeses de volta, seu canalha!";
			link.l1 = ""+RandSwear()+"!!!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Que bom ver o senhor. Alguma novidade?";
			link.l1 = "Encontrei seu homem. Hoje à noite ele vai entregar um vinho 'batizado' para a guarnição da prisão. Ele conseguiu uma poção com uma cigana, não é letal, mas eles vão dormir como pedras. Você precisa entrar lá hoje e tirar seus cavalheiros capturados. Ah, essa entrega de vinho me custou vinte e cinco dobrões. Não esqueça de mencionar isso no relatório.";
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = "Não se preocupe com o dinheiro. Capitão, quero que você venha com a gente nessa operação e nos mostre o caminho até a prisão. Você já esteve em Philipsburg antes, então conhece a cidade melhor do que nós. Não precisa entrar na prisão com a gente, vamos cuidar da fuga por conta própria. Só nos leve até a porta.";
			link.l1 = "Maldição, Sr. Gretton, esse trabalho só fica cada vez melhor. Espero que o pagamento esteja aumentando na mesma medida.";
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = "Com certeza é, capitão. Você não vai se arrepender de nos ajudar. Seu navio está na Praia Grand Case?";
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = "Sim.";
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = "Não.";
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = "Ótimo. Então se prepare e nos encontre nos portões da cidade às onze horas da noite.";
			link.l1 = "Te vejo lá.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = "Leve ela para lá, porque precisamos tirar nossos homens pela selva. Zarpar do porto ou da Baía Simpson é impossível por causa do forte. Prepare tudo e encontre a gente nos portões da cidade às onze da noite.";
			link.l1 = "Te vejo lá.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("Voice\English\Gr_hovernor01.wav");
			dialog.text = "Pronto, capitão?";
			link.l1 = "Sim.";
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = "Então vamos nessa.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = "Quieto... Capitão! Já foi, vamos dar o fora daqui!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = "Eu não sei como conseguimos, mas conseguimos! Nada disso teria sido possível sem a sua ajuda, senhor. Agora vem a parte relativamente fácil – precisamos sair de Sint Maarten vivos e inteiros. Vamos para a Praia de Grand Case!";
			link.l1 = "Vamos!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Capitão "+pchar.lastname+"... "+GetAddress_Form(NPChar)+", thank you for your assistance! I beg you, please don't leave port immediately, but stay here for one more day while I report to Colonel Fox. Pay him a visit tomorrow; his office is in the governor's palace.";
			link.l1 = "Muito bem, tenente Gretton. Espero que valha a pena para mim. Vai levar muito tempo para eu recuperar minha reputação com os holandeses por causa da sua aventura.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Obrigado pela sua ajuda, capitão! Você "+GetSexPhrase("agiu como um verdadeiro herói","é uma jovem muito corajosa")+", "+GetAddress_Form(NPChar)+"!   É uma tragédia que o tenente Gretton não tenha sobrevivido. Ele morreu como um verdadeiro cavalheiro e filho da Inglaterra. Gostaria de pedir para ficar aqui mais um dia enquanto faço meu relatório ao coronel Fox. Visite-o amanhã, o escritório dele fica no palácio do governador.";
			link.l1 = "Muito bem. Espero que valha a pena para mim. Vai levar muito tempo para eu recuperar minha reputação com os holandeses por causa da sua aventura.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = "Não se preocupe, "+GetAddress_Form(NPChar)+". Vou lhe dar o maior reconhecimento possível no meu relatório. (saúda) Foi um prazer, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "...";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("Voice\English\soldier_common_2.wav");
			dialog.text = "Capitão "+GetFullName(pchar)+"?";
			link.l1 = "Hm... Sim, o que posso fazer por você?";
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = "O escritório do porto nos informou sobre a recente chegada do seu navio. Sua Excelência Mynheer Martin Thomas, o governador de Philipsburg, deseja vê-lo.";
			link.l1 = "Por quê? Estou sendo preso?";
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			AddLandQuestMark(characterFromId("Marigo_Mayor"), "questmarkmain");
			dialog.text = "Ah não, não, "+GetAddress_Form(NPChar)+" capitão, você não está preso. O governador ordenou que todo capitão recém-chegado seja convidado ao palácio para um café e uma apresentação. Venha comigo!";
			link.l1 = "Parece uma proposta irrecusável. Mostre o caminho.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("Voice\English\hol_gov_complete.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", mostre onde você viu aqueles soldados ingleses.";
			link.l1 = "Eles estão escondidos numa caverna na selva, como bandidos comuns.";
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = "Vamos, estamos te seguindo!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("Voice\English\hol_gov_quest.wav");
			dialog.text = "Espere, capitão! Você disse que encontrou os espiões ali — perto da entrada da caverna?";
			link.l1 = "Sim. Eu vi eles entrarem rapidamente depois que falaram comigo.";
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = "O mais provável é que eles ainda estejam lá dentro. Se a gente atacar todo mundo junto, eles vão recuar pra dentro da caverna. Vai ser um inferno tirar eles de lá... Vamos agir com inteligência. Capitão, vá lá sozinho e distraia eles. Eu e meus homens vamos até aquele poço seco ali na esquina. Ele dá direto dentro da caverna. Os desgraçados não vão perceber a gente chegando por trás\nVocê entra e, se os espiões ainda estiverem lá, converse com eles, faça perguntas idiotas, mantenha eles ocupados. Quando tiver toda a atenção deles - xingue o mais sujo que conseguir. Você é marinheiro, isso deve ser fácil pra você. Esse vai ser nosso sinal. Dois dos meus homens vão guardar a entrada principal pra impedir que fujam por ali. Vamos pegar esses caras.";
			link.l1 = "Seu plano parece perigosíssimo pra minha saúde. Do jeito que vejo, eles vão tentar me matar primeiro.";
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = "Não se preocupe, capitão. Seu objetivo é gritar o mais alto que puder assim que avistar o grupo de invasores. Se eles te atacarem – então corra e continue gritando. Meus homens são bem treinados, então relaxe, eles vão derrubar esses espiões antes que você se machuque.";
			link.l1 = "É bom que sim. Estou indo lá.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("Voice\English\hol_gov_common.wav");
			dialog.text = "Eram uns desgraçados duros... Muito bem feito, capitão, os cães ingleses foram derrotados. Os sabotadores foram eliminados, o comandante e o governador vão ficar satisfeitos.";
			link.l1 = "Demorou, hein, senhor...";
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = "A culpa foi da corda, tinha um balde na ponta que fazia um barulho danado. Tivemos que tomar cuidado.";
			link.l1 = "É... a corda. Tanto faz. Um dos seus patrulheiros desaparecidos está amarrado ali nos arbustos. Devem estar vivos ainda.";
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = "Deixe comigo. Você deveria ir até a cidade e descansar um pouco. Amanhã, faça uma visita ao nosso governador, ele já terá recebido meu relatório com muitos elogios sobre você.";
			link.l1 = "Vou fazer isso. Boa sorte, senhor.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
			if (GetCharacterIndex("marigojailoff") != -1)
			{
				DelLandQuestMark(characterFromId("marigojailoff"));
			}
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = "O que posso fazer por você, meu filho?";
			link.l1 = "Olá, pastor, só por curiosidade, há quanto tempo os marinheiros cativos confessaram?";
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = "Ontem à noite, meu filho... (sussurrando) Imagino que você já saiba que o plano foi traído?";
			link.l1 = "Eu não estaria aqui se não fosse por isso. O tenente Casper Gratton e os homens dele estão na selva agora. Todos estão vestidos como soldados holandeses, mas precisamos de mais ajuda porque os guardas da prisão estão esperando por eles.";
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = "(em voz alta) Rezei todos os dias para salvar a alma anglicana dele da danação! (sussurrando) Tenho um plano, mas preciso de duas dúzias de dobrões de ouro para conseguir tudo o que preciso.";
			link.l1 = "Plano caro. Pra que é o dinheiro?";
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = "Being a prison guard is dull work. To keep up morale, the officer in charge orders wine every evening to go with their dinner. The wine is brought from a warehouse I have access to. There is a gypsy woman in town who owes me a favour; she will make us a sleeping potion. All I need is to buy a few bottles of good wine, add the potion, and swap the bottles in the warehouse. That's why I need the gold.";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "Eu tenho os dobrões. Pegue-os.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Deixe-me voltar ao meu navio e pegar um pouco para você.";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			npchar.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = "Ah, meu filho, você trouxe a 'doação' de que falamos?";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "Sim, aqui.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Logo vou conseguir isso...";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveDublonsFromPCharTotal(24);
			dialog.text = "Perfeito. Venha me ver amanhã, no mesmo horário – eu lhe direi o resultado.";
			link.l1 = "Muito bem...";
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = "Saudações, meu filho.";
			link.l1 = "O mesmo pra você, pastor. Alguma novidade?";
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = "Sim. Está feito. O vinho foi 'temperado' e os guardas vão ter um agrado especial esta noite. Eles jantam às nove da noite, e até a meia-noite todos vão estar dormindo. Essa é sua única chance de agir, não vai ter outra. Tome cuidado, não dá pra confiar totalmente no seu disfarce de holandês.";
			link.l1 = "Entendi. Não vamos perder tempo. Até logo.";
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			AddLandQuestMark(sld, "questmarkmain");
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
