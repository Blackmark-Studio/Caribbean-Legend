// Ришард Шамбон - контрабандист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Cai fora, amigo. Não tenho nada a dizer pra quem ataca os outros sem motivo!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> кольцо
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "Oh! Aí está você. Eu estava prestes a sair à sua procura. Preciso de você, amigo.";
				link.l1 = "Você está estranhamente amigável hoje, Richard. Vamos, diga logo. O que você quer?";
				link.l1.go = "ring";
				break;
			}
			// <-- кольцо
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "O que você quer? Para ser sincero, hoje não estou de bom humor – na verdade, nem lembro a última vez que estive.";
				link.l1 = "É mesmo tão ruim assim, amigo?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! "+TimeGreeting()+"! O que você quer?";
				link.l1 = LinkRandPhrase("Ei Richard, ouviu alguma novidade ultimamente?","Aconteceu alguma novidade na ilha?","Vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria ver se seu humor melhorou. Tchau!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ruim? Não, não é ruim, mas também não é bom. Então... o que você quer?";
			link.l1 = "Só para dizer oi. Sou novo por aqui, então estou só andando pela ilha e conhecendo as pessoas.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Sério? Tudo bem, então. Eu sou Richard Shambon. Há muito tempo, eu negociava mercadorias valiosas – algumas até ilegais – mas, nos últimos nove anos, tenho vasculhado destroços de navios, procurando sucata e trocando por comida e ouro.";
			link.l1 = "E eu sou "+GetFullName(pchar)+", um capitão...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Quer dizer ex-capitão, ha-ha!";
			link.l1 = "Well, actually, my ship is in Blueweld now; I sailed here on a barque.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Sério? Impossível! E onde está sua barca agora?";
			link.l1 = "No fundo...";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Oh... Eu pensei... Ah, deixa pra lá, amigo. Vou tomar um rum...";
			link.l1 = "Boa sorte com isso. Foi bom conversar com você. Até a próxima.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Ei Richard, ouviu alguma novidade ultimamente?","Aconteceu alguma novidade na ilha?","Vai me contar as últimas fofocas?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quero te fazer algumas perguntas sobre a ilha.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// Кольцо
		case "ring":
			dialog.text = "Eu não era antes? Ah, todo mundo tem dias ruins! Mas enfim, dizem por aí na ilha que você é um excelente lutador. Me conta, é verdade?";
			link.l1 = "Eu não sei o que andam dizendo por aí, mas sei muito bem como manejar uma espada.";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;
		
		case "ring_1":
			dialog.text = "Ótimo. Escute, "+pchar.name+", lembra de eu te contar sobre o anel externo, e sobre as coisas valiosas que você pode encontrar lá?";
			link.l1 = "Richard, todo mundo tem falado sobre isso. Parece que caçar aquele anel é o único passatempo nesta ilha — além das intrigas políticas.";
			link.l1.go = "ring_2";
		break;
		
		case "ring_2":
			dialog.text = "Você disse tudo, ha-ha! Vou direto ao assunto. (baixando a voz) Encontrei um navio intacto no anel externo. Está em bom estado, o que é raro.\nO navio é grande: uma pinassa. Ele foi trazido para cá há pouco tempo – uns dois meses, mais ou menos. Ninguém mais percebeu ainda, então temos uma chance de ganhar um bom dinheiro saqueando ele.";
			link.l1 = "Você quer que eu vá com você?";
			link.l1.go = "ring_3";
		break;
		
		case "ring_3":
			dialog.text = "Exatamente! A proa da chalupa está toda amassada, e aqueles malditos caranguejos conseguiram entrar e fizeram um ninho inteiro no porão. Não tem como entrar sem que eles percebam, e eu não faço ideia de como subir até o convés principal a partir da linha d'água.\nNão sou bom de briga – faz anos que nem encosto numa lâmina – então nunca conseguiria matar essas criaturas sozinho. Por isso vim falar com você.";
			link.l1 = "Então você quer que eu mate todos os caranguejos dentro daquele navio para você...";
			link.l1.go = "ring_4";
		break;
		
		case "ring_4":
			dialog.text = "Sim. Aqui está minha proposta: eu te mostro o caminho até o navio, você elimina os caranguejos, e a gente divide qualquer tesouro que encontrar por lá.";
			link.l1 = "Não, amigo, não estou interessado. Não vale a pena enfrentar uma horda de caranguejos dentro de um navio meio afundado por uma recompensa duvidosa. Procure alguém mais imprudente para te ajudar.";
			link.l1.go = "ring_exit";
			link.l2 = "Interessante... Faz tempo que penso em explorar o anel externo. Fechado! Me mostre o naufrágio e eu acabo com os caranguejos.";
			link.l2.go = "ring_5";
		break;
		
		case "ring_exit":
			dialog.text = "Too bad... You're making a mistake; untouched wrecks are a rarity on the outer ring. Oh well, it's your choice. Goodbye...";
			link.l1 = "Tchau, Richard...";
			link.l1.go = "exit";
		break;
		
		case "ring_5":
			dialog.text = "Fico feliz por ter acertado sobre você, amigo. Tenho a sensação de que vamos encontrar muitas coisas interessantes lá dentro...";
			link.l1 = "Vamos ver. Você faz ideia de quantos caranguejos tem lá dentro?";
			link.l1.go = "ring_6";
		break;
		
		case "ring_6":
			dialog.text = "Acho que uns quatro ou cinco... Bem, que eu tenha visto.";
			link.l1 = "Tudo bem... quando vamos?";
			link.l1.go = "ring_7";
		break;
		
		case "ring_7":
			dialog.text = "Que tal amanhã? Precisamos de tempo para nos preparar. Pegue alguns antídotos com o Irmão Julian – as pinças do caranguejo são venenosas. Melhor prevenir do que remediar. Vamos nos encontrar amanhã às oito da manhã no convés inclinado. Sabe onde fica?";
			link.l1 = "Não, onde?";
			link.l1.go = "ring_8";
		break;
		
		case "ring_8":
			dialog.text = "There's an old wreck behind the San Augustine. Her bow is underwater and her rear is raised high; that's why she's called the 'canted deck.' You can only get aboard her by swimming.\nGet into the water on either side of the rop bridge, then swim around either the bow or stern of the San Augustine and climb onto the canted deck. We'll swim to our untouched wreck from there.";
			link.l1 = "Certo. Até amanhã!";
			link.l1.go = "ring_9";
		break;
		
		case "ring_repeat":
			dialog.text = "Oito horas, no convés inclinado.";
			link.l1 = "Sim, sim, eu vou lembrar...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;
		
		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
			AddQuestRecord("LSC_Ring", "1");
		break;
		
		case "ring_10":
			dialog.text = "Ah, aí está você, amigo. Pronto para preparar uma salada de caranguejo?";
			link.l1 = "Claro!";
			link.l1.go = "ring_11";
		break;
		
		case "ring_11":
			dialog.text = "Certo. Agora, vire a cabeça para o anel externo e olhe. Está vendo ali dois navios naufragados saindo da água?";
			link.l1 = "Hm... Sim, estou vendo eles.";
			link.l1.go = "ring_12";
		break;
		
		case "ring_12":
			dialog.text = "Olhe entre eles para o anel externo. Vê o galeão com a proa apontada para nós?";
			link.l1 = "...";
			link.l1.go = "ring_look";
		break;
		
		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;
		
		case "ring_13":
			dialog.text = "";
			link.l1 = "Sim, eu... eu acho que estou vendo!";
			link.l1.go = "ring_13a";
		break;
		
		case "ring_13a":
			dialog.text = "She's our target; our pinnace is hiding behind her. Swim straight and don't turn. I will show you the way from there, and how to get back to the island when we're done.\nThe entrance to the cargo hold is the hole in the pinnace's bow. I won't enter her until you kill all the crabs.";
			link.l1 = "Eu me lembro do nosso acordo. Você me mostra o caminho e eu cuido dos caranguejos. Vamos?";
			link.l1.go = "ring_14";
		break;
		
		case "ring_14":
			dialog.text = "Vamos sim. Eu vou te seguir.";
			link.l1 = "...";
			link.l1.go = "ring_swim";
		break;
		
		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			LSC_RingSetItems(); // раскладка итемзов
			AddQuestRecord("LSC_Ring", "3");
		break;
		
		case "ring_15":
			dialog.text = "Heh, mandou bem! Parece que você pegou todos eles!";
			link.l1 = "Eu me lembro claramente de alguém me dizer que eram só 'quatro ou cinco'...";
			link.l1.go = "ring_16";
		break;
		
		case "ring_16":
			dialog.text = "Olha, amigo, eu não fiz uma chamada, só dei uma espiada pelo buraco. Eu jamais mentiria de propósito!";
			link.l1 = "Tanto faz. Vamos procurar no porão de carga...?";
			link.l1.go = "ring_17";
		break;
		
		case "ring_17":
			dialog.text = "Claro! É por isso que estamos aqui.";
			link.l1 = "Certo, não vamos perder tempo...";
			link.l1.go = "ring_18";
		break;
		
		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;
		
		case "ring_wait":
			dialog.text = "Espere um pouco, amigo, ainda não olhei todos os lugares que queria. Procure com mais atenção, talvez encontre mais coisas de valor.";
			link.l1 = "Tudo bem...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;
		
		case "ring_19":
			dialog.text = "Nothing special. It's a pity that there aren't any high-value goods here; just casks of corned beef and boxes of copra. I did find a case of expensive wine, though. What do you have?";
			link.l1 = "Não muita coisa: algumas coisas de valor, mas o resto é carne salgada e copra, como você disse.";
			link.l1.go = "ring_20";
		break;
		
		case "ring_20":
			dialog.text = "Não é o bastante... Vamos subir e verificar os conveses superiores e as cabines.";
			link.l1 = "Vamos.";
			link.l1.go = "ring_21";
		break;
		
		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			}
		break;
		
		case "ring_22":
			dialog.text = "Droga! Olha só pra isso! Essas malditas caranguejos estão por toda parte! Como é que subiram até aqui?!";
			link.l1 = "Fique calmo! Fique aqui, não se mexa e fique quieto. Eu vou cuidar deles...";
			link.l1.go = "ring_23";
		break;
		
		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;
		
		case "ring_24":
			dialog.text = "Então as histórias sobre sua habilidade com a espada eram verdadeiras! Se eu estivesse aqui sozinho, já teria pulado no mar faz tempo.";
			link.l1 = "E como é que você conseguiu ser contrabandista no passado, hein, se perde a coragem tão fácil assim?";
			link.l1.go = "ring_25";
		break;
		
		case "ring_25":
			dialog.text = "Primeiro, eu era mais jovem, mais forte e mais imprudente. Segundo, não sou soldado – nós, contrabandistas, sempre tentamos evitar derramamento de sangue. Terceiro, meu talento está em lidar com velas e lemes, não com lâminas e pistolas. E quarto, os anos vivendo aqui me deixaram mais mole!\nEntão não fique bravo comigo. Vamos dar uma olhada no convés superior. Parece que o navio enfrentou uma briga feia. Olhe só esse estrago...";
			link.l1 = "Você tem razão. O navio realmente foi muito atingido. Vamos continuar procurando.";
			link.l1.go = "ring_26";
		break;
		
		case "ring_26":
			dialog.text = "E precisamos encontrar as entradas para as cabines dos oficiais.";
			link.l1 = "Então não vamos perder tempo. Me chame se vir um caranguejo!";
			link.l1.go = "ring_27";
		break;
		
		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;
		
		case "ring_28":
			dialog.text = "Nada, de novo! Só algumas bijuterias e mais nada. Mas tudo bem, normalmente não tem nada de valor nos conveses. O melhor deve estar nas cabines. Tem uma entrada para os aposentos do capitão ali. Vamos dar uma olhada.";
			link.l1 = "Tome cuidado, quem sabe o que nos espera lá dentro. Talvez seja melhor eu entrar primeiro?";
			link.l1.go = "ring_29";
		break;
		
		case "ring_29":
			dialog.text = "Vamos, "+pchar.name+". Eu não vou mais me esconder atrás de você.";
			link.l1 = "Pode ir então...";
			link.l1.go = "ring_30";
		break;
		
		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;
		
		case "ring_31":
			dialog.text = "It looks like we got lucky: neither crabs nor other filth in here. But fuck, I'm starting to get angry; I only found a couple dozen doubloons and a few sundries!";
			link.l1 = "Calma. Lembre-se: objetos de valor sempre ficam guardados na cabine do capitão. Vamos ver o que encontramos!";
			link.l1.go = "ring_32";
		break;
		
		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
			npchar.quest.diagnode = "ring_33";
		break;
		
		case "ring_33":
			dialog.text = "Ha-ha! Just as I thought! I know the habits of merchants; they like to create secret stashes around the ship and hide their treasures there! The captain of this pinnace was a cunning rogue, but I won't be so easily cheated! Look what I found!";
			link.l1 = "Mostre-me!";
			link.l1.go = "ring_34";
		break;
		
		case "ring_34":
			dialog.text = "Quarenta mil pesos, dois baús cheios de dobrões, um pacote de esmeraldas e um monte de joias! O dono era bem rico. Pelo menos vai compensar nosso esforço, embora eu esperasse encontrar mais coisas. Vamos dividir o saque.";
			link.l1 = "Excelente, Richard. Pelo menos não vamos sair de mãos vazias!";
			link.l1.go = "ring_35";
		break;
		
		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received 25 emeralds");
			Log_Info("You have received  a collection of jewels");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bem, vamos ficar cada um com o que encontrou nos conveses. Tudo bem pra você? Achou algo bom nos baús e armários?";
			link.l1 = "Alguns artefatos indígenas, amuletos, papéis e assim por diante.";
			link.l1.go = "ring_36";
		break;
		
		case "ring_36":
			dialog.text = "Fique com eles para você. No fim das contas, foi você quem fez o trabalho mais arriscado.";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Certo. E aqui vai algo que um caçador de tesouros como você pode achar útil: encontrei o diário de bordo do capitão em cima daquela mesa. A história que ele conta é bem triste, mas pode ajudar na nossa busca. Tem uma caixa escondida em algum lugar do porão cheia de ouro! Aqui, leia!";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
				{
					link.l1 = "Certo. Mas encontrei mais uma coisa: o diário de bordo do capitão.";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "Não vou discordar disso, ha-ha! Então, hora de voltar?";
					link.l1.go = "ring_37";
				}
			}
		break;
		
		case "ring_37":
			dialog.text = "Yes. Don't tell anyone about the ship; it'll be our secret. Sure, we don't need copra, but all that food will be useful; we won't have to buy from the Admiral anymore.";
			link.l1 = "Está bem, eu concordo. Espero que ninguém encontre este navio tão cedo. Vamos!";
			link.l1.go = "ring_cabin_exit";
		break;
		
		case "ring_38":
			dialog.text = "Você leu?";
			link.l1 = "Ainda não...";
			link.l1.go = "ring_39";
		break;
		
		case "ring_39":
			dialog.text = "Então vamos ler! Podemos aprender algo importante com isso. E vai ser interessante descobrir como o navio veio parar aqui. Leia!";
			link.l1 = "Hum. Tá bom, vou ler agora...";
			link.l1.go = "ring_40";
		break;
		
		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;
		
		case "book_wait":
			dialog.text = "Você leu? O que tem lá?";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Eu li. Olha, a história é bem triste, mas revela que tem uma caixa escondida cheia de ouro no porão do navio! Leia, talvez você consiga descobrir onde está.";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "Espere um segundo. Vou ler e te contar...";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;
		
		case "ring_41":
			dialog.text = "Sério? "+pchar.name+", eu... bem, não leio muito bem. Me diz o que está escrito aí, hein?";
			link.l1 = "Resumindo: esta chalupa cruzava o Mar do Caribe de sul a norte, seguindo a costa da Nova Espanha. No caminho, o capitão se apaixonou e se casou com uma princesa indígena de uma tribo do baixo Orinoco. Ela contou a ele que seu povo realizava sacrifícios...";
			link.l1.go = "ring_42";
		break;
		
		case "ring_42":
			dialog.text = "";
			link.l1 = "Os sacrifícios deles eram pepitas de ouro! Então é claro que nosso capitão roubou o ouro com a ajuda do imediato e do contramestre. Eles colocaram tudo numa caixa no porão e cobriram com copra...";
			link.l1.go = "ring_43";
		break;
		
		case "ring_43":
			dialog.text = "";
			link.l1 = "Mas parece que o roubo daquele lugar sagrado dos índios foi castigado: o navio ficou à deriva, a água acabou, a febre se espalhou e piratas atacaram. Os marinheiros culparam a índia — esposa do capitão — e exigiram que ele a jogasse ao mar. Claro que o capitão se recusou, e então houve um motim...";
			link.l1.go = "ring_44";
		break;
		
		case "ring_44":
			dialog.text = "";
			link.l1 = "O capitão perdeu a luta. Pelos últimos registros dele, ele se trancou com a esposa indígena na cabine e atirou em quem tentasse arrombar a porta. Ele menciona que uma tempestade se aproximava — provavelmente foi isso que trouxe o navio para a Ilha da Justiça. No fim, a esposa dele foi baleada, e não tenho dúvidas de que os amotinados acabaram matando ele também.";
			link.l1.go = "ring_45";
		break;
		
		case "ring_45":
			dialog.text = "Hum, sim, sim, uma história triste... mas o ouro... será que tem mesmo uma caixa de pepitas de ouro no porão? Em qual delas?! Vamos procurar! Eu reviro todo o porão se for preciso!";
			link.l1 = "Tá bom, tá bom, sim, vamos procurar - calma, Richard!";
			link.l1.go = "ring_seek_gold";
		break;
		
		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // убираем журнал
			AddQuestRecord("LSC_Ring", "6");
		break;
		
		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ставим прерывание на локатор
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// подменяем состав бокса
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;
		
		case "ring_46":
			dialog.text = "Ha-ha! Achamos! Olha só esse brilho! Uma caixa inteira! Não deve ter menos de cinco mil pepitas aqui! Nunca vi tanto ouro!!";
			link.l1 = "Parabéns, parceiro. Parece que todo o nosso esforço valeu a pena! O que vamos fazer com todo esse ouro?";
			link.l1.go = "ring_47";
		break;
		
		case "ring_47":
			dialog.text = "O que você quer dizer? Nós vamos dividir isso ao meio!";
			link.l1 = "Quero dizer, onde você vai guardar isso? Vai deixar aqui?";
			link.l1.go = "ring_48";
		break;
		
		case "ring_48":
			dialog.text = "Ha! No, I'll hide the gold in my own private stashes where no one will ever find them. Hiding is the one thing I know well how to do! Let's put half the gold into this barrel - that'll be my share. I'll take it away before sunset.\nYou do whatever you want with you share, but you'd do well to move it into your own stashes, too. Don't blame me if you find your gold missing; I'm an honest man, in my way, and I won't touch your cut. But very soon, others may find this ship, and they won't hesitate to grab whatever they find.";
			link.l1 = "Obrigado. Vou pensar no que fazer com meu ouro. Enquanto isso, vamos colocar sua parte naquele barril...";
			link.l1.go = "ring_49";
		break;
		
		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later..."+ NewStr() +"The gold was shared!", "", 0, 5);//табличка
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;
		
		case "ring_50":
			dialog.text = "Pronto... Obrigado, "+pchar.name+", por ter vindo comigo. Eu não teria conseguido sem você. Agora, acho que devo pensar em construir uma tartana... zarpar daqui...\nAh, vou me preocupar com isso depois. Por enquanto, já vai dar trabalho suficiente esconder esse ouro nos meus esconderijos. Adeus, amigo, espero que use sua parte com sabedoria!";
			link.l1 = "Tchau, Richard. Foi um dia glorioso. Fique bem!";
			link.l1.go = "ring_51";
		break;
		
		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Perguntas? Ah, tudo bem, se você insiste...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Como você veio parar aqui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Você quer deixar a ilha?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Você já pensou em se juntar a um dos clãs? Os Narvais, por exemplo?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "É verdade que dá pra encontrar muita coisa interessante no anel externo?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Com licença...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Por dez anos, eu e meus camaradas navegamos de Cuba até esta ilha e de volta, numa tartana, para negociar com os locais. Mantínhamos o paradeiro da ilha em segredo e trocávamos carne fresca, frutas e legumes por mercadorias e ouro dos porões dos navios naufragados. Bons tempos!  O abastecimento sempre foi um problema para o povo da Ilha da Justiça, então eles nos pagavam muito bem por carne suculenta com especiarias, que custa uma fortuna lá na Europa! Em cada viagem, eu ganhava dinheiro suficiente para comprar todas as prostitutas de Tortuga.  Mas tudo tem um fim. As tempestades nesta região ficaram mais fortes e frequentes, então navegar até a ilha se tornou muito mais perigoso. Alguns da minha tripulação abandonaram o negócio, mas eu e uma dúzia de rapazes corajosos continuamos firmes.  Por fim, uma tempestade nos lançou contra um recife a duas milhas da ilha. Até hoje não entendo como consegui atravessar aquele mar revolto a nado. Agora sou um dos que antes eram meus clientes.";
			link.l1 = "História interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ha! Um dia ainda vou sair daqui, droga, mas não como um miserável! O que eu faria em Cuba? Não tenho mais amigos lá e estou sem um tostão no bolso.\nSó preciso encontrar um navio no anel externo com o porão cheio de carga valiosa, ou uma pilha de dobrões. Aí construo uma nova tartana, enfrento as tempestades e volto pra civilização.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_3":
			dialog.text = "Por que eu faria isso? Ficar de guarda, torrando no sol a cada três dias, impedindo as pessoas de chegarem perto do San Gabriel? Além disso, eles não gostam de contratar quem não é da ilha — afinal, são nativos... Os Negros são iguais. Então não, prefiro ficar por conta própria.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Claro! É assim que os moradores sobrevivem. Sabe quando eles gostam de fazer festas? Quando um novo navio encalha no anel.\nAinda há muitos destroços intocados cheios de ouro e mercadorias por aí, mas explorar o anel externo é perigoso. Aquilo lá é uma bagunça, e você não vai querer se aventurar sozinho. Se ficar preso em algum cabo ou escorregar e cair, já era. Muita gente já morreu assim.";
			link.l1 = "Hum... Vou tomar cuidado então.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ei, tira as mãos do meu esconderijo, ladrão!","Não se pode confiar em ninguém nesta ilha! Em guarda, ladrão!","Larga do meu baú do mar, seu desgraçado!");
			link.l1 = "Vai se foder!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Assaltar uma mulher inocente?! Você não vai sair impune dessa!";
			link.l1 = "Garota tola!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Guarde sua arma. Você está me deixando nervoso.","A menos que pretenda usar essa lâmina, é melhor guardá-la.","Guarde essa arma, você está assustando as pessoas – eu incluso!");
			link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Desculpa...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"A menos que pretenda usar essa lâmina, é melhor guardá-la.","Guarde sua arma. Você está me deixando nervoso.");
				link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Guarde sua arma. Você está me deixando nervoso.","Guarde essa arma, você está assustando as pessoas – eu incluso!");
				link.l1 = RandPhraseSimple("Entendi.","Eu vou levar isso embora.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
