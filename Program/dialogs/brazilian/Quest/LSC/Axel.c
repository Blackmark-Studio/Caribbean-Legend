// торговец Аксель Йост
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
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Olha só isso..."+GetFullName(pchar)+"! Voltou do mundo dos mortos? Como conseguiu isso?";
				link.l1 = "Simples: eu nunca morri, ha-ha!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Heh, camarada, não faço negócio com você até você se acertar com os Narvais. Não quero confusão com eles. Fale com o Fazio, ele pode te ajudar.";
				link.l1 = "Tudo bem, vou vê-lo imediatamente.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Não quero falar com você, camarada. Você ataca pessoas inocentes sem motivo e ainda provoca briga. Cai fora!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ah, um rosto novo! O que te traz aqui? Mas talvez não seja da minha conta perguntar... Deixe-me me apresentar: meu nome é Axel Yost e esta é minha loja. Viu algo de que goste?";
				link.l1 = TimeGreeting()+". Meu nome é "+GetFullName(pchar)+". Que tipo de mercadorias você está vendendo?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+pchar.name+"! Que bom te ver. Veio comprar ou vender?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1")
				{
					link.l4 = "Escuta, Axel, você tem um bom rifle à venda? Não um mosquete comum de soldado, veja bem, mas algo com precisão e alcance altos?";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "trader_whiskey")
				{
					link.l4 = "Escuta, Axel, o Chad Kapper te pediu um barril de uísque? ";
					link.l4.go = "whiskey";
				}
				if (CheckAttribute(npchar, "quest.ole_pearl"))
				{
					link.l5 = "Escuta, Axel, você deve ter ouvido minha conversa com aquele idiota. Que conta ele pediu? Não entendi.";
					link.l5.go = "ole_pearl";
				}
				link.l1 = "Sim. Vamos negociar, Axel!";
				link.l1.go = "Trade_items";
				link.l2 = LinkRandPhrase("Ouviu alguma novidade pela ilha, Axel?","O que tem acontecido na ilha ultimamente?","Que fofoca você ouviu recentemente?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Ainda não. Só queria dizer oi.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Todo tipo de coisa: poções, lâminas, armas de fogo, munição, couraças, gemas, minerais, amuletos encantados, talismãs, bugigangas, materiais de criação...\nO pessoal me traz tudo que encontra nos destroços – coisas que não precisam – então fique à vontade para fazer o mesmo. Claro, não trabalho com mantimentos nem mercadorias de navio.";
			link.l1 = "Parece bom, Axel. Vamos ver o que você tem.";
			link.l1.go = "Trade_items";
			link.l2 = "Obrigado, Axel, vou me lembrar disso. Nos vemos quando eu precisar dos seus serviços.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Trade_items":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 5)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// наводка на Адольфа
		case "adolf":
			dialog.text = "Isso só pode ser uma piada. Você é a terceira pessoa a me perguntar isso!\nEu não tenho esse tipo de arma, mas alguns meses atrás o Adolf Barbier tentou me vender o stutzen de caça dele, com luneta. Uma arma maravilhosa, vou te dizer, exatamente o que você procura.\nMas o Barbier pediu um preço absurdo, então recusei a oferta dele.";
			link.l1 = "Sério! E onde posso encontrar Barbier?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Não faço ideia. Ele provavelmente está vagando pela cidade. Costuma visitar a taverna do Sancho, gosta de tomar um drinque toda noite.";
			link.l1 = "Obrigado! Acho que vou procurá-lo lá. Me diga, Axel, quem mais te perguntou sobre o rifle? Você mencionou que outros estavam interessados, quem seriam eles?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Mary Casper and Marcello - also known as Cyclops.\nI have no idea why that girl would be in need of a rifle, but then, our Red Mary is a well-known madcap. A year ago, she bought out tons of gun powder to make mines - 'To stun crabs,' she said. Thank the Lord Donald talked her out of it.\nAnd Marcello wanted to buy a rifle for bird hunting; says he got tired of salted beef. I referred them both to Adolf. I don't know if he sold the rifle to one of them or not.\nAlso... that sly dog Giuseppe Fazio inquired about Adolf recently. Perhaps he wants to buy the stutzen, too.";
			link.l1 = "Parece que tenho muita concorrência. Tudo bem, vou procurar o Adolf – tomara que ele ainda não tenha vendido o stutzen.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_2"; //флаг на таверну
			AddQuestRecord("SharkHunt", "12");
			sld = characterFromId("LSC_Adolf");
			sld.lifeday = 0; // убираем настоящего Адольфа
		break;
		
		// бусинка для Белого Мальчика - просто инфа
		case "ole_pearl":
			dialog.text = "Heh, é assim que ele chama pérolas grandes! Ele pede isso pra todo mundo. Dê uma pra ele, e você vai ser o melhor amigo dele.";
			link.l1 = "Ah, entendi. Pérolas grandes... Obrigado, Axel. Eu teria me acabado procurando por contas comuns!";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.ole_pearl");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Sim, camarada, ele comprou sim. Mas se você também está querendo comprar um barril de Bushmills, vou te decepcionar. Eu só tinha um barril e o Chad levou. Posso te oferecer uísque escocês – é tão bom quanto o irlandês e, pra falar a verdade, eu até prefiro o sabor dele.";
			link.l1 = "Outra hora. O Chad comprou mais alguma coisa de você?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "No. Oh! He was interested in arsenic, said that there are too many rats on the Tartarus and he wants to get rid of them.\nI don't carry arsenic anymore, haven't needed it since I hired Ole to clean my shop. I gave my reserve to poor Sancho; the rats seemed to have picked up and moved into his tavern. I don't know why rats fear Ole so much...";
			link.l1 = "Talvez o pai dele fosse um gato.";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Ha-ha! Talvez... De qualquer forma, o Sancho tem arsênico, se você precisar de um frasco.";
			link.l1 = "Tudo bem, obrigado. Vou vê-lo agora mesmo.";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			DialogExit();
			AddQuestRecord("SharkHunt", "36");
			pchar.questTemp.Saga.SharkHunt = "barmen_whiskey"; // флаг на таверну - поиск мышьяка
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
