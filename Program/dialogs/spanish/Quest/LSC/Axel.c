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
				dialog.text = "¿Mira eso...?"+GetFullName(pchar)+"¡¿Has regresado del más allá?! ¿Cómo es posible?";
				link.l1 = "La gente no vuelve del más allá, Axel. Es simple, ¡no he estado muerto, ja-ja!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Heh, amigo, no haré negocios contigo antes de que arregles las cosas con los Narvales. No quiero problemas. Ve a Fazio, él puede encargarse de esto.";
				link.l1 = "Está bien, lo haré de inmediato.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "No quiero hablar contigo. Atacas a gente pacífica sin razón y los provocas a pelear. ¡Piérdete!";
				link.l1 = "Mm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "¡Oh! ¡Una cara nueva! ¿Qué te trae por aquí? Aunque, no es asunto mío. Permíteme presentarme: mi nombre es Axel Yost y soy el dueño de esta tienda. ¿Ves algo que te guste?";
				link.l1 = TimeGreeting()+". Mi nombre es "+GetFullName(pchar)+"¿Qué tipo de mercancías tienes?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+pchar.name+"¡Me alegra verte! ¿Quieres comprar o vender algo?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1")
				{
					link.l4 = "Escucha, Axel, ¿tienes un buen mosquete para vender? No una pistola casual de soldado, sino algo para disparos precisos y de largo alcance?";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "trader_whiskey")
				{
					link.l4 = "Escucha, Axel, ¿Chad Kapper te pidió que le consiguieras un barril de whisky? ";
					link.l4.go = "whiskey";
				}
				if (CheckAttribute(npchar, "quest.ole_pearl"))
				{
					link.l5 = "Escucha, Axel, debiste haber oído mi conversación con ese idiota. ¿Qué abalorio pidió? No lo entiendo.";
					link.l5.go = "ole_pearl";
				}
				link.l1 = "Sí. ¡Hagamos un trueque, Axel!";
				link.l1.go = "Trade_items";
				link.l2 = LinkRandPhrase("¿Tienes algo interesante que contar?","¿Qué ha sucedido recientemente en la Isla?","¿Algún chisme?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Aún no. Solo quería saludarte.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Todo tipo de cosas. Mezclas, hojas, armas de fuego, municiones, corazas, gemas y minerales. Amuletos y talismanes encantados. Basura y objetos cotidianos. La gente me trae todo lo que encuentra en los barcos naufragados, cosas que no necesitan ellos mismos\nAsí que siéntete libre de hacer lo mismo. Sin embargo, debo advertirte. No ofrezco provisiones ni mercancías de barco.";
			link.l1 = "Bien, Axel. Vamos a ver tus mercancías.";
			link.l1.go = "Trade_items";
			link.l2 = "Gracias, Axel. Lo tendré en cuenta. Te veré tan pronto como necesite tus servicios.";
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
			dialog.text = "Esto debe ser una especie de broma. Eres la tercera persona en preguntar. No llevo ese tipo de armamento aquí. Pero hace varios meses, Adolf Barbier intentó venderme su stutzen de caza con mira telescópica. Un arma maravillosa, te lo digo. Exactamente lo que estás buscando. \nPero Barbier pidió un precio demencial por ella. Así que tuve que rechazar su oferta.";
			link.l1 = "¡Interesante! ¿Y dónde puedo encontrar a Barbier?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "No tengo ni idea. Probablemente esté deambulando por ahí. A menudo visita la taberna de Sancho, le gusta tomar una copa cada noche.";
			link.l1 = "¡Gracias! Creo que lo encontraré allí. Dime, Axel, ¿quién más te ha preguntado por el rifle? Mencionaste a otros que estaban interesados, ¿quiénes serían?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Mary Casper y Marcello, también conocido como Cíclope. No tengo idea de por qué la chica necesitaría un rifle, pero nuestra María Roja es una loca bien conocida. Hace un año, compró toneladas de pólvora para hacer minas, para aturdir cangrejos, dijo ella. Gracias al Señor, no se lo permitieron\nY Marcello quería comprar un rifle para cazar aves, el hombre se cansó de la carne salada. Los referí a ambos a Adolfo, no sé si compraron el rifle de él o no\nAdemás, ese perro astuto Giuseppe Fazio preguntó por Adolfo recientemente. Quizás, también quiera comprar este stutzen.";
			link.l1 = "Heh, tengo muchos competidores. Bien, iré a buscar a Adolf - con suerte, aún no ha vendido el arma.";
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
			dialog.text = "¡Todo el mundo lo sabe, señor! Él le pide a todos estas cuentas, así es como llama a las grandes perlas. Dale una, y serás su mejor amigo.";
			link.l1 = "Ahora veo. Gracias, Axel, nunca lo habría adivinado yo mismo.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.ole_pearl");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Sí, amigo, lo hizo. Pero te decepcionaré si también quieres comprar un barril de Bushmills. Solo tenía un barril y Chad lo compró. Puedo ofrecerte whisky escocés, es tan bueno como el irlandés y, de hecho, me gusta mucho más el sabor.";
			link.l1 = "Tal vez, más tarde. ¿Chad te ha comprado algo más?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "No. Dijo que estaba interesado en el arsénico, que hay demasiadas ratas en el Tártaro y quiere exterminarlas. No he necesitado arsénico desde que contraté a ese idiota de Olle para limpiar mi tienda, todas las ratas se han ido a la taberna del pobre Sancho. No sé por qué las ratas temen tanto a Olle...";
			link.l1 = "Tal vez, tiene gatos en su familia...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "¡Ja, ja! Quizás... Sancho tiene arsénico - eso es seguro.";
			link.l1 = "Ya veo. ¡Gracias por la información, entonces!";
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
