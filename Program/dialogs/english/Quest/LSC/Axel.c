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
				dialog.text = "Would you look at that..."+GetFullName(pchar)+"! Back from the dead? How'd you manage that?";
				link.l1 = "Simple: I never died, ha-ha!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Heh, pal, I won't do business with you until you make peace with the Narwhals. I don't want any trouble from them. Talk to Fazio, he can help you.";
				link.l1 = "Fine, I'll see him immediately.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "I don't want to talk to you, pal. You attack innocent people for no reason and provoke them to fight. Get lost!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ah, a new face! What brings you here? Though, maybe it's not my place to ask... Let me introduce myself: my name is Axel Yost and this is my shop. See anything you like?";
				link.l1 = TimeGreeting()+". My name is "+GetFullName(pchar)+". What kind of goods are you selling?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+pchar.name+"! Glad to see you. Looking to buy, or sell?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1")
				{
					link.l4 = "Listen, Axel, do you have a fine rifle for sale? Not a casual soldier's musket, mind, but something with high accuracy and range?";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "trader_whiskey")
				{
					link.l4 = "Listen, Axel, did Chad Kapper ask you to get him a barrel of whiskey? ";
					link.l4.go = "whiskey";
				}
				if (CheckAttribute(npchar, "quest.ole_pearl"))
				{
					link.l5 = "Listen, Axel, you must have heard my conversation with that simpleton. What bead did he ask for? I don't get it.";
					link.l5.go = "ole_pearl";
				}
				link.l1 = "Yes. Let's trade, Axel!";
				link.l1.go = "Trade_items";
				link.l2 = LinkRandPhrase("Hear any news around the island, Axel?", "What's been happening on the island lately?", "What gossip have you heard recently?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Not yet. Just wanted to say hello.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "All kinds of stuff: potions, blades, firearms, ammo, cuirasses, gems, minerals, enchanted amulets, talismans, garbage, crafting materials...\nPeople bring me everything they find on the wrecks - things they don't need themselves - so feel free to do the same. Of course, I don't offer provisions or ship's wares.";
			link.l1 = "Sounds good, Axel. Let's see what you have.";
			link.l1.go = "Trade_items";
			link.l2 = "Thanks, Axel, I'll keep that in mind. I'll see you when I've need of your services.";
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
			dialog.text = "This must some kind of a joke. You're the third person to ask that!\nI don't carry such weaponry, but several months ago Adolf Barbier tried to sell me his scoped hunting stutzen. A wonderful weapon, let me tell you, exactly what you're looking for.\nBut Barbier asked a hell of price for it, so I rejected his offer.";
			link.l1 = "Really! And where can I find Barbier?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "I have no idea. He's probably wandering around the city. He often visits Sancho's tavern, likes to have a drink every evening.";
			link.l1 = "Thanks! I think I'll look for him there. Tell me, Axel, who else has asked you about the rifle? You mentioned others who were interested, who would they be?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Mary Casper and Marcello - also known as Cyclops.\nI have no idea why that girl would be in need of a rifle, but then, our Red Mary is a well-known madcap. A year ago, she bought out tons of gun powder to make mines - 'To stun crabs,' she said. Thank the Lord Donald talked her out of it.\nAnd Marcello wanted to buy a rifle for bird hunting; says he got tired of salted beef. I referred them both to Adolf. I don't know if he sold the rifle to one of them or not.\nAlso... that sly dog Giuseppe Fazio inquired about Adolf recently. Perhaps he wants to buy the stutzen, too.";
			link.l1 = "Seems I've got a lot of competition. Fine, I'll go find Adolf - hopefully, he hasn't sold the stutzen yet.";
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
			dialog.text = "Heh, that's what he calls large pearls! He asks everyone for them. Give him one, and you will be his best friend.";
			link.l1 = "Ah, I see. Large pearls... Thank you, Axel. I would have run myself ragged looking for ordinary beads!";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.ole_pearl");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Yes, pal, he did. But if you're looking to buy a barrel of Bushmills too, I have to disappoint you. I only had the one barrel and Chad bought it. I can offer you Scotch whisky - it's as good as Irish, and, actually, I like the taste more.";
			link.l1 = "Another time. Did Chad buy anything else from you?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "No. Oh! He was interested in arsenic, said that there are too many rats on the Tartarus and he wants to get rid of them.\nI don't carry arsenic anymore, haven't needed it since I hired Ole to clean my shop. I gave my reserve to poor Sancho; the rats seemed to have picked up and moved into his tavern. I don't know why rats fear Ole so much...";
			link.l1 = "Maybe his father was a cat.";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Ha-ha! Maybe... Anyway, Sancho has arsenic, if you need a bottle.";
			link.l1 = "All right, thanks. I'll see him right away.";
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
