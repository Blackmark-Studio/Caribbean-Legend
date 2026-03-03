// Гхерад Смиитс - матрос
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
				dialog.text = "Cai fora, camarada. Não converso com quem ataca gente inocente!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "E aí, camarada, ha-ha! O que você está fazendo aqui?";
				link.l1 = TimeGreeting()+". Bom dia! Acho que ainda não tive o prazer de te conhecer.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ei, "+GetFullName(pchar)+"! "+TimeGreeting()+"! O que posso fazer por você?";
				link.l1 = LinkRandPhrase("E aí! Alguma novidade?","Aconteceu alguma novidade na ilha?","Vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Até mais!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Claro, você não conhecia, mas agora conhece! Meu nome é Gerard Smeets, marinheiro — um homem do mar de Roterdã. E você parece um imediato, se não me engano...?";
			link.l1 = "Algo assim. Meu nome é "+GetFullName(pchar)+". Prazer em conhecê-lo.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Na verdade, você parece mais um dono de navio ou um tesoureiro... Sem dúvida, é um homem instruído. Prazer em conhecê-lo! Como veio parar aqui?";
			link.l1 = "Decidi explorar o Golfo do México. Bucaneiros de Cuba me contaram que havia uma ilha desconhecida nessa região e eu queria ver se era verdade.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Você é o único sobrevivente? Onde seu navio afundou, no anel externo?";
			link.l1 = "I'm indeed the only one. And my barque is at the bottom of the sea south of here; it didn't even reach the outer ring.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Ah. Bem, já que você está preso aqui, passe no Sancho para pegar um pouco de rum. Afogar as mágoas é um bom começo pra sua estadia, he-he.";
			link.l1 = "Obrigado... até mais!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("E aí, Smeets, alguma novidade?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quero te fazer algumas perguntas sobre a ilha.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Claro, pode mandar!.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Me diga, como você veio parar aqui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Você quer deixar a ilha e voltar para a sua antiga vida?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "As tribos te incomodam?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Como essa ilha se formou? Alguma ideia?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Com licença...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "I got here with that puffed up peacock Abbot. I served on his ship. You know, people like him ought never set foot on a ship's deck - they bring bad luck. The devil must've put him on our tub.\nWe set sail on a voyage from Jamaica to Belize; easy as pie. But ill fate chased us: our boatswain fell overboard, our navigator steered us wrong, the bloody Spanish fell upon us, and a storm battered us to pieces. And here we are.";
			link.l1 = "Meu Deus!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "I used to, but... tell ye the truth, mate, I don't know. Life is fine here; plenty of rum and wine, good food - not a lot, but  better than weevilly ship's biscuits.\nThere are good blokes here, plenty of drink and gabbin'. I like it here. So I'm not sure... No, I reckon I don't want to leave. I used to live angry and hungry - look at my belly now, ha-ha!";
			link.l1 = "Ótimo! Fico feliz por você.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "No, they don't. Just don't trespass against 'em, they don't abide that. The Narwhals are good lads - most of 'em were born here and they know no other life. Many of 'em are very skilled. Jurgen Schmidt for example; he's a god of blacksmithing, Hephaestus in the flesh!";
			link.l1 = "Bom saber.";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Storms and reefs, mate. The outer ring is made of ships top to bottom; ships get caught by a storm and thrown onto the reefs or the outer ring itself. That's how the island grows!\nThough I've no idea why the inner ships stay above the water. Probably there's a shoal beneath our feet, holding us up.";
			link.l1 = "Fascinante!";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ei, ladrão! Achou que podia me roubar na cara dura, é?","Viro as costas, olha só o que acontece! Um ladrão imundo aparece rastejando!","Ei! Tira as mãos do meu baú do mar, camarada!");
			link.l1 = "Ah, que se dane!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Revistando meus baús?! Como você ousa!";
			link.l1 = "Droga...";
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
			dialog.text = LinkRandPhrase("Amigo, guarda essa lâmina, vai? Você tá me deixando nervoso.","Não deixe ninguém te ver correndo por aí com uma lâmina na mão. Guarda isso.","Não fique bancando o cavaleiro com a espada desembainhada, você está pagando de idiota. Guarda isso...");
			link.l1 = LinkRandPhrase("Tudo bem.","Como quiser...","Como você diz...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escuta, a gente não tolera idiotas andando por aí com armas na mão. Guarda isso.","Não gosto de homem que fica tão à vontade com a lâmina. Guarde isso.");
				link.l1 = LinkRandPhrase("Tudo bem.","Tanto faz então.","Como você disser...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Amigo, guarda essa lâmina, vai? Você tá me deixando nervoso.","Não gosto de homem que vive puxando a lâmina. Isso me assusta...");
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
