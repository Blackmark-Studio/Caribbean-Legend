// Юрген Шмидт - оружейник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iRem;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Escuta aqui, senhor, por que você começou uma briga, hein? Você não tem nada que fazer na minha oficina, a menos que seja nosso inimigo. Cai fora!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Ouvi falar dos seus feitos. É bom que você tenha se tornado amigo do Donald e nosso aliado. Os Narvais sabem valorizar a amizade, posso garantir isso.";
					link.l1 = "Espero que sim. Posso contar com seus serviços agora?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "E aí? O que você quer?";
					link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+". E eu só estou andando por aí, conhecendo as pessoas. Estou te incomodando?";
				link.l1.go = "meeting";
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Ouvi falar dos seus feitos. É bom que você tenha se tornado amigo do Donald e nosso aliado. Os Narvais valorizam a amizade, posso te garantir isso.";
					link.l1 = "Espero que sim. Posso contar com seus serviços agora?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Quer conversar de novo? Tenho que te decepcionar, não tenho nem tempo nem vontade para isso.";
					link.l1 = "Tudo bem, não vou te incomodar.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Exatamente! Você está me incomodando, senhor. Eu sou Jurgen Schmidt, armeiro e ferreiro do clã Narval. Eu forneço armas para o nosso povo. Mas leva tempo para fazer uma boa lâmina, uma chave, uma fechadura, ou consertar o mecanismo de um mosquete de torre. Isso exige muito tempo, paciência e atenção. Por isso não gosto quando me atrapalham.";
			link.l1 = "Você fabrica armas? Posso encomendar algo com você?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Não. Eu só faço armas para membros do clã Narval. Esse é o meu princípio e vou mantê-lo. Então nem pense nisso, senhor. Junte-se ao nosso clã ou pelo menos torne-se nosso aliado, e aí sim podemos conversar.";
			link.l1 = "Tudo bem. Vou te deixar então. Desculpe por incomodar!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "friend":
			dialog.text = "Pode sim. Um amigo de Narval é meu amigo também, então estou ouvindo você.";
			link.l1 = "Gostaria de encomendar uma lâmina.";
			link.l1.go = "blade";
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l2 = "I've heard that you made a special blade for the late Alan Milrow. I've seen that broadsword; it's a fine weapon. Can I order something like that?";
				link.l2.go = "narval";
			}
			link.l3 = "Ainda não tenho ideias. Vou pensar um pouco e depois volto!";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "Jurgen":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ha, "+GetFullName(pchar)+"! Então você não se afogou? Que coisa! Você está mesmo vivo?";
				link.l1 = "Não se preocupe, Jurgen. Estou vivo! Eu não ia me afogar...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				NextDiag.TempNode = "Jurgen";
				break;
			}
			dialog.text = "Ah, "+GetFullName(pchar)+"! O que você quer?";
			if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
			{
				if (GetCharacterItem(pchar, "jewelry11") >= 3)
				{
					link.l4 = "Trouxe as três peças de ferro especial que você pediu. Veja só, era isso mesmo que queria?";
					link.l4.go = "narval_7";
				}
				if (CheckCharacterItem(pchar, "meteorite"))
				{
					link.l5 = "Dá uma olhada, Jurgen. Encontrei um lingote de ferro interessante lá no fundo, mas ele pesa bem mais do que você pediu. Pelo menos cinco libras.";
					link.l5.go = "narval_7_1";
				}
			}
			if (!CheckAttribute(npchar, "quest.blade_done"))
			{
				link.l1 = "Quero encomendar uma lâmina.";
				if (!CheckAttribute(npchar, "quest.blade_rules")) link.l1.go = "blade";
				else link.l1.go = "blade_4";
			}
			if (CheckAttribute(npchar, "quest.blade_payseek"))
			{
				link.l1 = "Trouxe mais dobrões como pagamento pela lâmina.";
				link.l1.go = "blade_3";
			}
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
			{
				link.l2 = "Ouvi dizer que você fez uma lâmina especial para o falecido Alan Milrow. Já vi aquela espada larga, é uma bela arma. Posso encomendar algo parecido?";
				link.l2.go = "narval";
			}
			if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
			{
				link.l1 = "Vim buscar meu pedido. Já deve estar pronto, não é?";
				link.l1.go = "blade_done_2";
			}
			link.l3 = "Não, não é nada, só queria te cumprimentar.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		// --> заказ клинков
		case "blade":
			dialog.text = "Certo. Mas tenho alguns requisitos especiais para qualquer pedido, então preste atenção primeiro.";
			link.l1 = "Estou ouvindo.";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "You may order only one blade from me, and only once. I don't make specific weapons; you may name only the type - rapier, saber, or broadsword. Think carefully before you make your choice; the final characteristics and quality of the blade will depend on the materials I have at the moment\nNow. It will take twenty days to craft your order. I accept only doubloons. One thousand coins. Payment upfront.";
			link.l1 = "Sério! Que caro...";
			link.l1.go = "blade_2";
		break;
		
		case "blade_2":
			dialog.text = "É caro. Mas eu faço lâminas excelentes, então o preço é justo. A decisão é sua, sem pressão.";
			link.l1 = "Entendo, Jurgen. Sim, gostaria de fazer um pedido.";
			link.l1.go = "blade_3";
			link.l2 = "Hum. Preciso de um tempo para pensar antes de pedir qualquer coisa para você. Depois conversamos sobre isso!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
			npchar.quest.blade_rules = "true";
			npchar.quest.blade_dublon = 1000;
			AddQuestRecord("LSC", "17");
		break;
		
		case "blade_3":
			dialog.text = "Muito bem. Então me dê seus doblões.";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.blade_pay = PCharDublonsTotal();
				link.l1 = "Aqui, por favor. Eu tenho "+FindRussianQtyString(sti(npchar.quest.blade_pay))+".";
				link.l1.go = "blade_pay";
			}
			link.l2 = "Hm. Infelizmente, não tenho nenhum comigo agora. Mas vou trazê-los para você, com certeza, e continuaremos nossa conversa.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "blade_4":
			dialog.text = "Então essa é mesmo a sua decisão final? Tem certeza?";
			link.l1 = "Sim, sou eu.";
			link.l1.go = "blade_3";
		break;
		
		case "blade_pay": // оплата
			if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // полная сумма
			{
				npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.blade_dublon)-sti(npchar.quest.blade_pay);
			npchar.quest.blade_dublon = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.blade_pay));
			Log_Info("You have given "+sti(npchar.quest.blade_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Perfeito. Você já me pagou pelo trabalho e pelos materiais, então posso começar agora.";
				link.l1 = "Posso fazer um pedido?";
				link.l1.go = "blade_done";
			}
			else
			{
				dialog.text = "Certo. Aceito seus dobrões. Você tem que me trazer "+FindRussianQtyString(sti(npchar.quest.blade_dublon))+" mais.";
				link.l1 = "Eu vou trazê-los para você quando eu os tiver.";
				link.l1.go = "exit";
				npchar.quest.blade_payseek = "true";
			}
		break;
		
		case "blade_done":
			DeleteAttribute(npchar, "quest.blade_payseek");
			dialog.text = "Claro! Qual tipo você prefere? Rapiers, sabres ou espadas largas?";
			link.l1 = "Rapiers. Gosto de armas elegantes e leves.";
			link.l1.go = "rapier";
			link.l2 = "Sables. Na minha opinião, são a melhor escolha.";
			link.l2.go = "sabre";
			link.l3 = "Espadas largas, com certeza! Cortar e picar!";
			link.l3.go = "palash";
		break;
		
		case "rapier":
			npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
			dialog.text = "Como quiser. Volte para buscar seu pedido em vinte dias, nem um dia antes.";
			link.l1 = "Obrigado! Te vejo em vinte dias. Adeus, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "sabre":
			npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
			dialog.text = "Como quiser. Volte para buscar seu pedido em vinte dias, nem um dia antes.";
			link.l1 = "Obrigado! Te vejo em vinte dias. Adeus, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "palash":
			npchar.quest.blade_done = SelectJurgenBladeDone("palash");
			dialog.text = "Como quiser. Volte para buscar seu pedido em vinte dias, nem um dia antes.";
			link.l1 = "Obrigado! Te vejo em vinte dias. Adeus, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "blade_done_1":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "blade_date");
			NextDiag.CurrentNode = "Jurgen";
			AddQuestRecord("LSC", "18");
		break;
		
		case "blade_done_2":
			dialog.text = "Sim. Sua lâmina está pronta. Por favor, pegue-a e use-a. Você vai entender que ela vale o preço assim que tocá-la.";
			link.l1 = "Obrigado, Jurgen.";
			link.l1.go = "blade_done_3";
		break;
		
		case "blade_done_3":
			DialogExit();
			NextDiag.CurrentNode = "Jurgen";
			GiveItem2Character(pchar, npchar.quest.blade_done);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "blade_date");
		break;
		
		// заказ палаша Нарвал для Мэри
		case "narval":
			dialog.text = "Infelizmente, meu amigo, tenho que recusar, por dois motivos. Primeiro, só faço uma espada larga dessas para um membro do clã Narval, e apenas para alguém especial. Segundo, não tenho os materiais para isso.";
			link.l1 = "E que ferro especial é esse que você precisa? Ouvi dizer que tiraram ele do fundo...";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Exatamente. Há pedaços desse metal espalhados por todo o nosso banco de areia. Não sei como vieram parar aqui. Mas o ferro é único, nunca enferruja e as lâminas feitas dele nunca perdem o fio. Então, se você conseguir esse ferro, talvez possamos resolver a situação. Mas ainda há um problema, você não é um Narval...";
			link.l1 = "Hum. Isso realmente importa?";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Sim. Pode achar que é um capricho meu, mas só farei uma espada larga dessas para um Narval.";
			link.l1 = "Bem... Tudo bem, eu aceito isso. Mas tenho uma ideia. Posso encomendar essa lâmina para um membro do clã Narval?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Hm. Suponho que sim, se você trouxer o ferro. Isso não vai contra meus princípios... E para quem você quer que eu faça a espada larga?";
			link.l1 = "Para a Mary Vermelha. Ela é do clã Narval e merece ter uma arma tão excelente.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Ha! Eu poderia ter descoberto isso sozinho. Estou ficando velho demais... Bem, concordo. Tenho certeza de que Mary vai ficar realmente feliz com esse presente... Traga o ferro e eu vou forjar a espada larga. Eu pegaria pelo menos pela lâmina... ah, deixa pra lá, vou fazer de graça. Vai ser um presente não só seu, mas nosso.";
			link.l1 = "Obrigado! De quanta quantidade de ferro você precisa?";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Aqueles pedaços que encontramos no fundo eram todos iguais — uma libra cada. Eu preciso de três pedaços como esses.";
			link.l1 = "Certo. Vou tentar encontrá-los. E conversaremos de novo.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			DialogExit();
			npchar.quest.narval_blade = "ferrum";
			NextDiag.CurrentNode = "Jurgen";
			// кладем гигантский кусок метеорита на дно
			sld = ItemsFromID("meteorite");
			sld.shown = true;
			sld.startLocation = "underwater";
			sld.startLocator = "item"+(rand(7)+1);
			Log_TestInfo("Meteorite in the locator " + sld.startLocator);
			pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
			pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
			pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
			AddQuestRecord("LSC", "19");
		break;
		
		case "narval_7":
			RemoveItems(pchar, "jewelry11", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Deixe-me ver... Sim, é isso mesmo! Foi difícil encontrar pedaços tão pequenos no fundo?";
			link.l1 = "Bem, o que posso dizer... A Mary vale esse esforço, não vale?";
			link.l1.go = "narval_8";
			pchar.quest.LSC_narval_ferrum.over = "yes"; //снять прерывание
		break;
		
		case "narval_7_1":
			RemoveItems(pchar, "meteorite", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Deixe-me ver... Mas veja só! Sim, é ferro de fundo, mas nunca vi pedaços tão grandes assim. Este aqui vai ser suficiente para fazer a espada larga. Foi difícil de encontrar?";
			link.l1 = "Bem, o que posso dizer... A Mary vale esse esforço, não vale?";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			dialog.text = "Gosto cada vez mais de você, "+pchar.name+"... Muito bem então. Agora é a minha vez de trabalhar em nome da nossa bela Amazona. Vai levar dois dias para fazer a espada larga, vou deixar outros pedidos de lado\nTraga a Mary para mim depois de amanhã. Não conte a ela, é surpresa. Ela vai ficar feliz como uma criança.";
			link.l1 = "Certo, Jurgen. Fechado! Te vejo depois de amanhã!";
			link.l1.go = "narval_9";
		break;
		
		case "narval_9":
			DialogExit();
			npchar.quest.narval_blade = "work";
			NextDiag.CurrentNode = "narval_10";
			SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // таймер
			AddQuestRecord("LSC", "21");
		break;
		
		case "narval_10":
			dialog.text = ""+pchar.name+", não me incomode. Você quer que eu termine a espada larga a tempo, não quer?";
			link.l1 = "Sim, claro. Estou indo embora.";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_10";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("O que você está fazendo aí, hein? Ladrão!","Olha só! No instante em que me perdi em contemplação, você resolveu mexer no meu baú!","Veio mexer nos meus baús? Não vai sair impune!");
			link.l1 = "Droga!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Olha, é melhor você guardar sua arma. Isso me deixa nervoso.","Sabe, andar por aí com uma lâmina na mão não é permitido aqui. Guarde isso.","Escuta, não fique bancando um cavaleiro medieval correndo por aí com uma espada. Guarda isso, não combina com você...");
			link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escute, eu sou um cidadão desta cidade e gostaria que você abaixasse sua espada.","Escute, eu sou um cidadão desta cidade e gostaria que você baixasse sua espada.");
				link.l1 = LinkRandPhrase("Tudo bem.","Certo.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Cuidado, amigo, andando por aí com uma arma. Você pode me deixar nervoso...","Eu não gosto quando homens passam na minha frente com as armas na mão. Isso me assusta...");
				link.l1 = RandPhraseSimple("Entendi.","Eu vou levar isso.");
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

string SelectJurgenBladeDone(string _sType)
{
	string sBlade;
	switch (_sType)
	{
		case "rapier":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_18"; 
			else sBlade = "q_blade_16";
		break;
		
		case "sabre":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_19"; 
			else sBlade = "q_blade_10";
		break;
		
		case "palash":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_21"; 
			else sBlade = "q_blade_13";
		break;
	}
	return sBlade;
}
