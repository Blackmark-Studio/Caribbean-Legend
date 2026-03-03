// Антонио Бетанкур - потомок Франциско Бетанкура
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
				dialog.text = "Saia da minha frente! Não quero papo com bandidos que atacam inocentes sem motivo. Vá embora!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Saudações! Em que posso ajudar você, amigo?";
				link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+" . Eu queria me apresentar. Veja, acabei de chegar e estou começando a conhecer a cidade e seu povo.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! O que posso fazer por você?";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "Antonio, dizem que você conhece bem a história da ilha. Tenho uma pergunta para você...";
					link.l4.go = "dolly";
				}
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Quer alguma coisa?";
				link.l1 = LinkRandPhrase("Quais são as novidades, Antonio?","Aconteceu alguma novidade na ilha?","Pode me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria ver como você está se saindo. Até logo, senhor!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Excelente. Bem-vindo à nossa ilha! Você vai se sair bem, porque aqui somos todos uma grande e feliz família – bem, exceto pelos Narvais e aqueles imundos Rivados, claro.\nMeu nome é Antonio, Antonio de Betancourt. Sou neto de Francisco de Betancourt, se esse nome lhe diz alguma coisa.";
			link.l1 = "Francisco de Betancourt? Já ouvi esse nome antes... Ah, claro! Jose Dios me falou dele, e li sobre ele nas anotações de Ignacio Alvarado!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Não conheço esse tal de 'Jose Dios' que você mencionou, mas o Capitão Alvarado nos visitou há muito tempo — eu mesmo o vi quando era criança. Ele partiu da ilha e escreveu sobre isso em seu diário. E meu avô, Francisco, foi um almirante espanhol, comandava seu próprio esquadrão.  Ele faz parte da história deste lugar porque os Rivados descendem dos escravos negros do Tártaro, o navio capitânia do esquadrão. Os Narvais são filhos dos primeiros colonos brancos: as tripulações do Tártaro, San Augustine e San Geronimo.";
			link.l1 = "Incrível! Então você nasceu aqui?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Exatamente. Sou neto do homem que colonizou a ilha.";
			link.l1 = "Entendi. Prazer em conhecê-lo, Antonio. Até logo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестовая часть
		case "dolly":
			dialog.text = "Claro, amigo, pode perguntar. Vou responder suas perguntas se eu puder.";
			link.l1 = "Me diga, você se lembra de um galeão chamado San Geronimo?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Claro que sim. Ela era um navio muito especial. Havia um ídolo indígena curioso a bordo, ao qual os pagãos imundos dos Rivados faziam sacrifícios.";
			link.l1 = "Que tipo de sacrifícios? Eles arrancavam corações e cortavam cabeças das pessoas como os maias faziam?";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "No. When a victim was brought to the idol, it dragged them into itself and they disappeared forever. Devil's work! Thank God above the idol sank with the ship and will do none harm any longer.\nThe sacrifices were always made in the morning; the idol used to turn to gold in the  rising sun's rays, so that was when the savages brought their victims - mostly Narwhals they'd captured.";
			link.l1 = "Fascinante! Alguém já tentou alcançar o ídolo?";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "Claro que não! Primeiro, os Rivados nunca deixam ninguém além dos seus chegar perto do San Geronimo, e segundo, um católico de verdade deve se manter longe das artimanhas do Diabo.";
			link.l1 = "Entendi... Imagino que você não goste muito dos Rivados.";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Good Lord, I hate those dirty pagans! As I said, my grandfather - God rest his soul - was captain of the ship upon which the negroes revolted, led by their leader, Rivados. Giving that black bastard a slow death was the only right and just response such actions.\nI had a gorgeous key to the St. Anna's treasury. No one knows where the treasury now lies - probably at the bottom of the sea with crabs picking over it - but the key was a sweet memento to me, and it was stolen!\nI am certain the blacks did it - trying to find the treasury! I doubt they'll succeed; it has been too long, ha-ha! Scum...";
			link.l1 = "Sim... aham, de qualquer forma, obrigado pela sua história interessante!";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "De nada! Volte quando quiser!";
			link.l1 = "Adeus!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Estou ouvindo, amigo.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Então, você nunca saiu da ilha?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Você nasceu aqui... mas não faz parte do clã Narval? Achei que todos os brancos nativos fossem Narvais.";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "E o que você faz na ilha?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Me diga, você já quis deixar a ilha, conhecer o mundo?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Com licença...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Nem uma vez sequer. Mas não pense que sou um tolo ou de mente fechada. Herdei uma bela biblioteca do meu avô, e meu pai me deu uma excelente educação. Conheço história, geografia, astronomia. Falo inglês, francês, espanhol, latim. Embora eu nunca tenha visto nada além de destroços de navios apodrecendo, em minha mente já visitei a Europa, a China, a Índia...\nNa verdade, diria que sei muito mais do que a maioria dos marinheiros que já deram a volta ao mundo.";
			link.l1 = "Talvez...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Nem todos, mas a maioria. Mas eu não sou um Narval e não quero me tornar um deles. Por que eu deveria? Para ficar de guarda horas a fio sob o sol escaldante ou ser esfaqueado numa briga com os Rivados? Deus me livre disso! Sou um intelectual. Prefiro viver por conta própria e ler meus livros.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Meu pai me deixou uma boa herança e eu a gasto com sabedoria, então não preciso rastejar por destroços de navios em busca de bugigangas para trocar por comida, nem correr atrás de tesouros que talvez nem existam. O único tesouro que eu realmente conheço é o cofre de St. Anna. Está guardado em um grande baú de ferro, mas ninguém conseguiu encontrar até agora. Um dia, vou escrever uma crônica detalhada da ilha baseada nas histórias orais dos moradores – o que acha disso?";
			link.l1 = "Uma busca valiosa! Conheço pelo menos um homem no Caribe que pagaria bem por um livro desses...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Às vezes. Se algum navio conseguisse navegar pelas correntes e tempestades, talvez eu arriscasse. Tenho tanta vontade de ver as coisas que são descritas com tanto detalhe nos meus livros! Mas, por enquanto, são apenas sonhos...";
			link.l1 = "Às vezes, os sonhos se realizam... se você fizer por onde.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ahh, socorro! Ladrão!!","Seu canalha, tentando me roubar enquanto viro as costas!","Tire as mãos disso! Esse baú é meu! Alguém, socorro!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "O que você pensa que está fazendo, mexendo nos meus baús? Você não vai sair impune dessa!";
			link.l1 = "Droga!";
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
			dialog.text = LinkRandPhrase("Guarde sua espada, senhor! Você me deixa nervoso.","Não é sensato andar por aqui com uma lâmina na mão, meu amigo. Guarde-a.","Ah, não saia por aí correndo com sua espada feito criança, guarde isso.");
			link.l1 = LinkRandPhrase("Tudo bem.","Como quiser...","Me desculpe...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Como cidadão desta cidade, exijo que guarde sua espada, senhor!","Guarde sua espada, senhor! Você está chamando atenção.");
				link.l1 = LinkRandPhrase("Certo.","Como quiser...","Como você diz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Amigo, por favor, guarde sua espada. Isso me deixa nervoso...","Eu não gosto de homens balançando suas armas na minha frente. Isso me assusta...");
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
