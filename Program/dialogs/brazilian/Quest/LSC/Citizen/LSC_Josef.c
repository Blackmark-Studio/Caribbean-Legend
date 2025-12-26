// Джозеф Лодердэйл - английский военный офицер
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
				dialog.text = "Vá embora, senhor! Você ataca inocentes e briga como um bandido qualquer! Saia da minha frente!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bom dia, senhor. Fico feliz em encontrar um nobre por aqui.";
				link.l1 = TimeGreeting()+". Na verdade, passei tanto tempo entre o povo comum durante minha estadia no Caribe que comecei a esquecer que sou nobre.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetFullName(pchar)+"! Que bom te ver! O que me diz?";
				link.l1 = LinkRandPhrase("Bom dia, Joseph! O que há de novo na ilha?","Aconteceu alguma novidade na ilha?","Vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria te deixar um abraço. Até logo!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Oh, e ainda por cima um nobre modesto! Um verdadeiro cavalheiro! Acho que você e eu vamos ser amigos – você não é como aquele abade arrogante... Permita-me apresentar: Capitão Joseph Lauderdale, da Marinha da Commonwealth.";
			link.l1 = "Prazer em conhecê-lo, Capitão. "+GetFullName(pchar)+" ao seu dispor!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "A vida aqui é bem monótona, então passe na taverna à noite e podemos tomar uma taça de vinho e conversar como verdadeiros cavalheiros.";
			link.l1 = "Vou me lembrar disso, senhor. Até logo!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Bom dia, Joseph. Como vão as coisas?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quero te fazer algumas perguntas sobre a ilha.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Será um prazer responder às suas perguntas, senhor.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Como você veio parar aqui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Que tipo de serviços podem ser encontrados na ilha?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Sendo um homem da marinha, qual é a sua opinião sobre o domínio dos piratas por aqui?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Já vi muitos baús trancados espalhados pela ilha. As pessoas aqui não confiam umas nas outras, não é?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Desculpe...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Cumpri meu dever. Estava lutando contra uma escuna de guerra espanhola, um navio que acreditávamos ser responsável por saquear vários comerciantes ingleses. O combate durou horas. Quase conseguimos pegá-los, mas uma tempestade repentina acabou com tudo: ambos os navios naufragaram perto do anel externo.\nO destino tem seu senso de humor, pois tanto eu quanto meu rival espanhol sobrevivemos. Talvez você já tenha cruzado com ele – chama-se Lorenzo Solderra, um bastardo papista dos mais raros. Tome cuidado com ele.";
			link.l1 = "Obrigado pelo seu relato, vou considerar seu aviso...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "If you need to rest, visit Sancho's tavern. He'll always provide you with food, drink, and a bed. If you need powder, shot, cold steel and the like, go to Axel Yost; he owns the local shop. Brother Julian offers medicines and sells holy amulets in his church.\nThe Narwhals have a very talented blacksmith, name of Jurgen Schmidt. They say that he crafts the most exquisite blades. There's another talented craftsman among the Narwhals, but I never learned anything about him.\nIf you run afoul of the pirates or the other clans, see Giuseppe Fazio; he functions as a sort of local diplomat between the clans.";
			link.l1 = "Obrigado pela informação!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "I can't say I like it, but there's nothing I can do about it - and even I must admit they established peace on the island in record time. Before the pirates arrived, the clans fought each other almost daily with no regard for the innocents caught in the middle.\nMoreover, the pirates sell food at a fair rate; citizens get good nutrition cheaply. But the pirates gouge the clans as revenge for attacking them when they first arrived.\nI know a very smart man among the pirates: Layton Dexter. He's in charge of all their trade. I had a talk with him once. I wonder how such a talented and educated man - who knows tactics, cartography and economics - wound up joining a band of pirates.\nYou know it only took him a few days to make a map of this whole island? I saw it, it has almost everything. I believe he made it in anticipation of a war between the clans...";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "É prudência, meu amigo, prudência. Dizem que antigamente, furtos eram comuns na ilha – pelo menos até instalarem novas fechaduras em todos os baús. E ainda assim... ainda há alguém que consegue abrir os baús. Mas ele só leva rum e bijuterias baratas, nunca ouro ou dinheiro. Cada fechadura é única, não existem chaves duplicadas – Jurgen Schmidt cuidou disso. Ele fabrica não só lâminas, mas também fechaduras e chaves. Ouvi dizer que os baús do lado de fora não guardam nada de valor, que as coisas importantes ficam sempre dentro dos navios.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Eu achei que você fosse um nobre, mas você não passa de um ladrão comum!","Tentando me roubar, é? Vou te mostrar como lidamos com ladrões na Marinha da Commonwealth!","Tire as mãos do meu baú do mar, ladrão!!");
			link.l1 = "Ah, merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ladrão! Alguém pare esse ladrão!";
			link.l1 = "Cale a boca!";
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
			dialog.text = LinkRandPhrase("Por favor, senhor, guarde sua espada. Você está chamando atenção.","Guarde sua espada, antes que alguém decida fazer você guardá-la.","Embora eu admire coragem em um homem, talvez agora não seja o melhor momento para brandir uma espada...?");
			link.l1 = LinkRandPhrase("Tudo bem.","Como quiser...","Como você disser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Pare com essas palhaçadas, senhor. Guarde sua espada.","Cavalheiro, por favor, guarde sua espada. Você está chamando atenção.");
				link.l1 = LinkRandPhrase("Tudo bem.","Como quiser...","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Cavalheiro, por favor, guarde sua espada. Você está chamando atenção.","Embora eu admire coragem em um homem, talvez agora não seja o melhor momento para ficar brandindo uma espada...");
				link.l1 = RandPhraseSimple("Desculpe.","Estou guardando isso.");
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
