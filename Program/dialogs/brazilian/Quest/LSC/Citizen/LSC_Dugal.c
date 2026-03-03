// Дугал Эббот - дворянин
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
				dialog.text = "Não vou falar com você, senhor. Você ataca pessoas pacíficas sem motivo. Saia da minha frente!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Saudações, senhor. Permita-me apresentar: Dougall Abbot. É bom ver um nobre por aqui. Esses camponeses são insuportáveis. Nunca imaginei que teria que passar o resto da vida entre pessoas tão insignificantes.";
				link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+". Prazer em te conhecer. E por que você não gosta dos moradores daqui?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! O que posso fazer por você?";
				link.l1 = LinkRandPhrase("Dougall! Que notícias da ilha?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Até logo!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Espere até conhecê-los melhor. Você acabou de chegar? Não me lembro de ter ouvido falar de um novo naufrágio...";
			link.l1 = "Vim para cá em uma pequena barca. Ela afundou de repente, no meio da noite.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Sim, acontece – navios afundam e só alguns sobreviventes conseguem chegar à costa. Às vezes, as pessoas vivem aqui por meses e você nunca chega a conhecê-las.";
			link.l1 = "Entendi. Foi bom conhecê-lo, Sr. Abbot. Adeus!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Saudações, Dougall! O que há de novo?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quero te fazer algumas perguntas sobre a ilha.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Estou ouvindo.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Como você veio parar aqui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "O que você pode me contar sobre os moradores daqui?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "O que você pode me contar sobre os clãs?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Como está o tempo? Vocês têm muitas tempestades por aqui?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Perdão...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "It was five years ago, but I still remember it as if it were yesterday. I'd set sail from Port Royal for Belize on a fluyt stuffed with high-value cargo.\nThe next day, things started to go wrong: first, my boatswain got drunk and fell overboard; then we almost hit a reef; then my navigator made a mistake and sent us north instead of south.\nA Spanish brig and galleon happened upon us. We fled and they gave chase. The galleon we left behind but the brig caught up to us.\nSince the galleon was too far back to support her smaller companion, I ordered that we come about and board the brig at once. The Spanish dogs weren't expecting that, he-he! (sigh) We won, but at the cost of most of my crew.\nMere hours later, a storm got up, and we couldn't weather it with so few crew, and now you see the result: my fluyt is wrecked somewhere on the outer ring, and me and  three other survivors live here now. Fuh!";
			link.l1 = "Que história e tanto.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Escória. Todos eles! Ptah! (cospe) Gente de baixo calão de todo tipo. Richard Shambon é um criminoso – está estampado na cara dele. Kassel? Matar para ele é tão natural quanto respirar. Jasper Pratt é um condenado. Musket é um bêbado. Preciso mesmo continuar?\nJoseph Lauderdale é o único homem decente aqui – tirando você, é claro. Ele é um oficial da Marinha inglesa. Há dois nobres aqui: Antonio de Betancourt e Lorenzo Solderra – malditos espanhóis! Eu não sento nem à mesma mesa que eles.";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "A bunch of bastards and scum. They don't harm us, though; they're far more interested in killing each other. And they've never stopped - can't live without violence.\nI don't like pirates either but I must admit the island has grown more peaceful since their arrival; they balance out the Narwhals and Rivados.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Nunca. Tempestades acontecem com frequência ao redor da ilha, mas a ilha em si está sempre tranquila. Talvez seja vontade de Deus ou algum feitiço, não sei. Às vezes temos ventos fortes e chuva, mas nada tão ruim a ponto de causar estragos.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ahá! Eu sabia que você era só um bandido qualquer, desde o momento em que pus os olhos em você!","Tira as mãos da minha propriedade, verme!","Tira essas mãos imundas do meu peito! Vou te atravessar por isso!");
			link.l1 = "Droga!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Nem pense em mexer nas minhas coisas, seu patife! Cai fora daqui!";
			link.l1 = "Calma, mulher!";
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
			dialog.text = LinkRandPhrase("Senhor, guarde sua arma. Você está me deixando nervoso.","Guarde sua arma, você está chamando atenção.","Você pode machucar alguém andando assim armado. Guarde isso, senhor.");
			link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Como você disser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Como um cavalheiro desta cidade, exijo que guarde sua arma!","Eu imagino que um cavalheiro como você não precisaria ficar brandindo uma arma por aí.");
				link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem então.","Como você diz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Senhor, guarde sua arma. Você está me deixando nervoso.","Peço que guarde sua arma, senhor. Você me deixa nervoso.");
				link.l1 = RandPhraseSimple("Muito bem.","Estou guardando isso.");
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
