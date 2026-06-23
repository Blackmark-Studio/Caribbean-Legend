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
				dialog.text = "Schau dir das an..."+GetFullName(pchar)+"! Bist du aus dem Jenseits zurück? Wie ist das möglich?";
				link.l1 = "Leute kommen nicht aus dem Jenseits zurück, Axel. Es ist einfach - Ich war nicht tot, ha-ha!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Heh, Kumpel, ich werde keine Geschäfte mit dir machen, bevor du die Dinge mit den Narwalen klärst. Ich möchte keine Schwierigkeiten. Geh zu Fazio, er kann das regeln.";
				link.l1 = "Gut, ich werde das sofort tun.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && int(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Ich will nicht mit dir reden. Du greifst friedliche Leute ohne Grund an und provozierst sie zum Kampf. Verschwinde!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh! Ein neues Gesicht! Was bringt dich hierher? Obwohl, das geht mich nichts an. Lass mich mich vorstellen: Mein Name ist Axel Yost und ich besitze diesen Laden. Siehst du etwas, das dir gefällt?";
				link.l1 = TimeGreeting()+". Mein Name ist "+GetFullName(pchar)+". Welche Art von Waren hast du?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+pchar.name+"! Froh dich zu sehen. Möchtest du etwas kaufen oder verkaufen?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1")
				{
					link.l4 = "Hör zu, Axel, hast du ein gutes Musketen zu verkaufen? Nicht irgendeine einfache Soldatenpistole, sondern etwas für genaues und weites Schießen?";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "trader_whiskey")
				{
					link.l4 = "Hör zu, Axel, hat Chad Kapper dich gebeten, ihm ein Whiskyfass zu besorgen? ";
					link.l4.go = "whiskey";
				}
				if (CheckAttribute(npchar, "quest.ole_pearl"))
				{
					link.l5 = "Hör zu, Axel, du musst mein Gespräch mit diesem lokalen Idioten gehört haben. Welche Perle hat er gefragt? Ich verstehe es nicht.";
					link.l5.go = "ole_pearl";
				}
				link.l1 = "Ja. Lass uns handeln, Axel!";
				link.l1.go = "Trade_items";
				link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu erzählen?","Was ist kürzlich auf der Insel passiert?","Gibt es Klatsch?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Noch nicht. Wollte dich nur begrüßen.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Alle möglichen Dinge. Mixturen, Klingen, Schusswaffen, Munition, Kürasse, Edelsteine und Mineralien. Verzauberte Amulette und Talismane. Müll und Alltagsgegenstände. Die Leute bringen mir alles, was sie auf den abgestürzten Schiffen finden, Dinge, die sie selbst nicht brauchen\nAlso zögern Sie nicht, das gleiche zu tun. Ich muss Sie allerdings warnen. Ich biete keine Proviant oder Schiffsausstattung an.";
			link.l1 = "Gut, Axel. Zeig uns deine Waren.";
			link.l1.go = "Trade_items";
			link.l2 = "Danke dir, Axel. Ich werde das im Hinterkopf behalten. Ich werde dich sehen, sobald ich deine Dienste benötige.";
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
			dialog.text = "Das muss ein Witz sein. Du bist die dritte Person, die danach fragt. Ich führe solche Waffen hier nicht. Aber vor einigen Monaten hat Adolf Barbier versucht, mir seinen Jagdstutzen mit Zielfernrohr zu verkaufen. Eine wunderbare Waffe, sage ich dir. Genau das, wonach du suchst. Aber Barbier hat einen Teufel von einem Preis dafür verlangt. Also musste ich sein Angebot ablehnen.";
			link.l1 = "Interessant! Und wo kann ich Barbier finden?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Ich habe keine Ahnung. Er streunt wahrscheinlich irgendwo herum. Er besucht oft Sanchos Taverne, er trinkt gerne jeden Abend einen Schluck.";
			link.l1 = "Danke! Ich denke, ich werde ihn dort finden. Sag mir, Axel, wer hat dich noch nach dem Gewehr gefragt? Du hast von anderen gesprochen, die interessiert waren, wer könnten sie sein?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Mary Casper und Marcello, auch bekannt als Zyklop. Ich habe keine Ahnung, warum das Mädchen ein Gewehr brauchen würde, aber unsere Rote Mary ist eine bekannte Verrückte. Vor einem Jahr hat sie Tonnen von Schießpulver gekauft, um Minen zu bauen, um Krabben zu betäuben, sagte sie. Gott sei Dank durfte sie das nicht tun\nUnd Marcello wollte ein Gewehr zum Vogeljagen kaufen, der Mann hatte genug von gesalzenem Rindfleisch. Ich habe sie beide an Adolf verwiesen, weiß nicht, ob sie das Gewehr von ihm gekauft haben oder nicht\nAuch dieser schlaue Hund Giuseppe Fazio hat sich kürzlich nach Adolf erkundigt. Vielleicht will er auch diese Stutze kaufen.";
			link.l1 = "Heh, ich habe viele Konkurrenten. Gut, ich werde Adolf suchen - hoffentlich hat er das Gewehr noch nicht verkauft.";
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
			dialog.text = "Das weiß jeder, Herr! Er fragt jeden nach diesen Perlen, so nennt er die großen Perlen. Gib ihm eine, und du wirst sein bester Freund sein.";
			link.l1 = "Jetzt verstehe ich. Danke, Axel, ich hätte es selbst nie erraten.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.ole_pearl");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Ja, Kumpel, das hat er. Aber ich werde dich enttäuschen, falls du auch ein Fass Bushmills kaufen willst. Ich hatte nur ein Fass und Chad hat es gekauft. Ich kann dir schottischen Whisky anbieten - er ist genauso gut wie der irische, und eigentlich mag ich den Geschmack viel lieber.";
			link.l1 = "Vielleicht später. Hat Chad noch etwas bei dir gekauft?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Nein. Er interessierte sich für Arsen, er sagte, es gäbe zu viele Ratten in der Tartarus und er wolle sie ausrotten. Seit ich diesen Idioten Olle eingestellt habe, um meinen Laden zu putzen, sind alle Ratten zur armen Sancho's Kneipe gegangen. Ich weiß nicht, warum Ratten Olle so sehr fürchten...";
			link.l1 = "Vielleicht hat er Katzen in seiner Familie...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Ha-ha! Vielleicht... Sancho hat Arsen - das ist sicher.";
			link.l1 = "Ich verstehe. Danke für die Information, dann!";
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

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
