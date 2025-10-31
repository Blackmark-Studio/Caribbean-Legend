// диалоги персонажей по квесту Мангароса
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "What do you want?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
		break;
		
		// Амелия - знахарка-цыганка
		case "amelia":
			dialog.text = "What do you want in my house?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Your name is Amelia, right? I came to ask you about a plant. Manga Rosa.";
				link.l1.go = "amelia_1";
			}
			else
			{
				link.l1 = "I have nothing to tell you yet. But I will be back one day...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "amelia";
		break;
		
		case "amelia_1":
			dialog.text = "Interesting! And who told you about me, brave young man?";
			link.l1 = "One of your people. She said that you know the secrets of this plant and that you can teach me how to make special potions from it...";
			link.l1.go = "amelia_2";
		break;
		
		case "amelia_2":
			dialog.text = "First, show me the plant you are talking about. Perhaps you don't know a thing about it and you're just wasting my time. Where is your Manga Rosa?";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Here, take a look.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "Hm...";
				link.l1.go = "amelia_exit";
			}
		break;
		
		case "amelia_exit":
			dialog.text = "And what were you going to show me? You don't have Manga Rosa. So get out, pal, before I lose my temper. This conversation is over.";
			link.l1 = "But...";
			link.l1.go = "exit";
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_wait":
			dialog.text = "You again? Don't cause any trouble, boy...";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Calm down, Amelia. I must have dropped it somewhere last time. Here, I have brought you Manga Rosa. Take a look.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "amelia_exit";
			}
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_3":
			dialog.text = "Let's see... It seems you know something about it. And do you want me to tell you the secrets of my potions?";
			link.l1 = "Exactly. And not for free, as I understand...";
			link.l1.go = "amelia_4";
		break;
		
		case "amelia_4":
			dialog.text = "You understand it right, young man! You don't look like a complete idiot. Well, I can teach a man who seeks knowledge and who doesn't waste this rare plant on useless smoking stuff...";
			link.l1 = "Amelia, before we start bargaining... would you be so kind as to tell me some basic knowledge about potions I can make from Manga Rosa?";
			link.l1.go = "amelia_5";
		break;
		
		case "amelia_5":
			dialog.text = "No bargaining, pal. I will tell you the price and it will be your decision whether to pay it or not. Don't count on any bargains or discounts, this is not a market. And concerning your question... You can make special potions of Manga Rosa which will fortify your physical abilities. They can make you stronger, more enduring or faster, or they can completely alter your body, making you stronger in every aspect, but such a potion would have a weaker effect than the previous two.";
			link.l1 = "Very interesting. Name your price.";
			link.l1.go = "amelia_6";
		break;
		
		case "amelia_6":
			dialog.text = "I can teach you three recipes. For each recipe, I ask for one plant and five hundred gold coins.";
			link.l1 = "Tell me more about these potions. What does each of them do?";
			link.l1.go = "amelia_7";
		break;
		
		case "amelia_7":
			dialog.text = "You must be a master of the art of alchemy if you wish to brew even a single potion. Each potion lasts for two days or less, depending on when you drink it; if you take it at midnight, it will last nearly two full days\nThe first potion increases your strength and endurance. You will fight better, take less damage, and carry more weight\nThe second potion will make you swifter, more agile, tireless, and it will also improve your aim\nThe third potion has effects half as strong as both previous potions. But it also grants you charm, self-confidence, and luck as well\nAll Manga Rosa-based potions have a positive effect on your health. You must drink only one potion at a time; never mix them, otherwise they will do you no good—on the contrary, you will suffer severe poisoning\nSo, handsome, are you ready to pay for the knowledge right now, or do you need time to think?";
			if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
			{
				link.l1 = "Yes, I am ready.";
				link.l1.go = "amelia_8";
			}
			link.l2 = "I need to think for a bit. This is a big decision to make.";
			link.l2.go = "exit";
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_next":
			if (!CheckAttribute(npchar, "quest.ChickenGod") && CheckCharacterItem(pchar, "talisman11")) {
				if (CheckAttribute(npchar, "quest.recipe_power") || CheckAttribute(npchar, "quest.recipe_fast") || CheckAttribute(npchar, "quest.recipe_total")) {
					link.chickengod = "Amelia, you seem to have a knack for such things. Can you tell me if there is a demand for such stones among your people? I find them everywhere - it's like everyone is obsessed with them!";
					link.chickengod.go = "chickengod";
				}
			}
			
			if (CheckAttribute(npchar, "quest.ChickenGod") && !CheckAttribute(npchar, "quest.ChickenGod.Complete") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.chickengod = "Here you go, Amelia. Just as you ordered: one hundred and thirteen adder stones.";
				link.chickengod.go = "chickengod_collected";
			}
		
			if (CheckAttribute(npchar, "quest.recipe_all"))
			{
				dialog.text = "Ah, it's you, young man! So, did my potions help you?";
				link.l1 = "They really did, Amelia. Thank you!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ah, it's you, young man! Want to buy some recipes?";
				if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
				{
					link.l1 = "Exactly. That is why I am here.";
					link.l1.go = "amelia_8";
				}
				
				link.l2 = "Not yet, Amelia. Just paying you a visit.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_8":
			dialog.text = "Very well. What kind of recipe would you like to buy?";
			if (!CheckAttribute(npchar, "quest.recipe_power"))
			{
				link.l1 = "The recipe for a potion of strength and endurance.";
				link.l1.go = "power";
			}
			if (!CheckAttribute(npchar, "quest.recipe_fast"))
			{
				link.l2 = "The recipe for the potion of agility and tirelessness.";
				link.l2.go = "fast";
			}
			if (!CheckAttribute(npchar, "quest.recipe_total"))
			{
				link.l3 = "The recipe for a complex potion.";
				link.l3.go = "total";
			}
		break;
		
		case "power":
			dialog.text = "Fine. I have named it the 'Tidal Wave'. Here, take the instructions. Read them carefully. And don't forget how to use it correctly!";
			link.l1 = "Thank you, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosapower");
			SetAlchemyRecipeKnown("mangarosapower");
			npchar.quest.recipe_power = true;
		break;
		
		case "fast":
			dialog.text = "Fine. I have named it the 'Squall'. Here, take the instructions. Read them carefully. And don't forget how to use it correctly!";
			link.l1 = "Thank you, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosafast");
			SetAlchemyRecipeKnown("mangarosafast");
			npchar.quest.recipe_fast = true;
		break;
		
		case "total":
			dialog.text = "Fine. I've named it the 'Sea Hug'. Here, take these instructions. Read them carefully. And don't forget how to use it properly!";
			link.l1 = "Thank you, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosatotal");
			SetAlchemyRecipeKnown("mangarosatotal");
			npchar.quest.recipe_total = true;
		break;
		
		case "recipe_exit":
			DialogExit();
			NextDiag.CurrentNode = "amelia_next";
			RemoveDublonsFromPCharTotal(500);
			RemoveItems(pchar, "cannabis7", 1);
			Log_Info("You have given 500 doubloons and one Manga Rosa");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.recipe_power") && CheckAttribute(npchar, "quest.recipe_fast") && CheckAttribute(npchar, "quest.recipe_total"))
			{
				npchar.quest.recipe_all = true;
				CloseQuestHeader("mangarosa");
			}
		break;
		
		case "chickengod":
			dialog.text = "Bax de adder, indeed! It is of little value, but it can be of use to those who know. Bring me one hundred and thirteen of them, and I'll open one of my chests for you.";
			link.l1 = "That's a whole pile of rocks! Why don't you tell me why you need them first?";
			link.l1.go = "chickengod_1";
		break;
		
		case "chickengod_1":
			dialog.text = "No, dear, if you need to ask, then this knowledge is of no use to you yet.";
			link.l1 = "And what is inside the chest you so generously promised to open?";
			link.l1.go = "chickengod_2";
		break;
		
		case "chickengod_2":
			dialog.text = "A great many things, useful for captains who do not disdain manual labour. Don't waste my time, dear, you can't collect that many pebbles anyway.";
			link.l1 = "We'll see about that!";
			link.l1.go = "exit";
			
			npchar.quest.ChickenGod = true;
		break;
		
		case "chickengod_collected":
			dialog.text = "Ha-ha-ha! It was a joke, dear!";
			link.l1 = "The joke will be on you when they burn you, witch, in your own hovel!";
			link.l1.go = "chickengod_collected_1";
		break;
		
		case "chickengod_collected_1":
			dialog.text = "That's not my fate, dear... You've made this gypsy proud! Here, this chest is yours to plunder.";
			link.l1 = "Thank you, Amelia. But I do hope there's something useful in there besides your old underwear...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			npchar.quest.ChickenGod.Complete = true;
			AddDialogExitQuestFunction("ChickenGod_AmeliaOpenChest");
		break;
	}
} 
