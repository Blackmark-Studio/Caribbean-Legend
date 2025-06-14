void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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

		//--> Встреча
		case "DiegoDeLanda_Meeting":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Sad story, isn’t it?";
				link.l1 = "Who are you?";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Greetings, captain.";
				link.l1 = "Wait! We’ve met before!";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "One. Two. Three.";
				link.l1 = "Let’s stop this performance. Who are you?";
				link.l1.go = "DiegoDeLanda_Meeting_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
			DelLandQuestMark(npchar);
		break;
		
		case "DiegoDeLanda_Meeting_2":
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				dialog.text = "You know what’s special about this crypt? Here lie two souls connected by blood. Father and son de Alameda. One fell to the hands of sinners, the other… hmm, found his way to the Lord.";
				link.l1 = "Don Fernando’s diary brought me here.";
				link.l1.go = "DiegoDeLanda_SantaMisericordia_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				dialog.text = "Did you see Lady Bishop? Sad fate, isn’t it? But I’m afraid it was deserved.";
				link.l1 = "You know Elizabeth?";
				link.l1.go = "DiegoDeLanda_LadyBeth_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				dialog.text = "Mortimer Grim.";
				link.l1 = "You knew him, of course?";
				link.l1.go = "DiegoDeLanda_Memento_2";
			}
		break;

		case "DiegoDeLanda_Meeting_Third_2":
			dialog.text = "\nThree more. At the count of six you’ll know everything.";
			link.l1 = " If I don’t get clear answers from you right now, then I...";
			link.l1.go = "DiegoDeLanda_Meeting_Third_3";
		break;

		case "DiegoDeLanda_Meeting_Third_3":
			dialog.text = "\nYou’re doing well, captain. You deserve to know my name. It’s Diego de Landa.";
			link.l1 = " Are you truly a priest?";
			link.l1.go = "DiegoDeLanda_Meeting_Third_4";
		break;

		case "DiegoDeLanda_Meeting_Third_4":
			dialog.text = "First and foremost, I’m an artist. But let’s not rush...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		//<-- Встреча
		
		//--> Святое Милосердие
		case "DiegoDeLanda_SantaMisericordia_2":
			dialog.text = "Ah... The diary. A remarkable thing — the written word. It’s like... a path in the dark. Leads you to where revelation awaits. Don Fernando often visited our parish. Especially in the last year.";
			link.l1 = "You serve in the local parish? You knew Don Fernando?";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_3";
		break;

		case "DiegoDeLanda_SantaMisericordia_3":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_4";
		break;

		case "DiegoDeLanda_SantaMisericordia_4":
			dialog.text = "I... observed his path. And that book you took. Do you know what’s special about it?";
			link.l1 = "It looks old.";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_5";
		break;

		case "DiegoDeLanda_SantaMisericordia_5":
			dialog.text = "Old? Oh no. It’s... enlightened. The Bible of Don de Alameda Sr. Every word in it is like a beacon in the dark. Take it. Help your brothers in Christ and then, perhaps... it will lead you to something... greater.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		//<-- Святое Милосердие
		
		//--> Леди Бет
		case "DiegoDeLanda_LadyBeth_2":
			dialog.text = "Oh, yes. Poor woman. Her husband… not the kindest man. They say his plantations are the most productive on Barbados. And the cruelest. Do you know how many slaves die there each month? Recently, he beat to death a real doctor from England — a man of great mind and talent. But her fate isn’t much better, believe me.";
			link.l1 = "You seem very well informed.";
			link.l1.go = "DiegoDeLanda_LadyBeth_3";
		break;

		case "DiegoDeLanda_LadyBeth_3":
			dialog.text = "People come to me for confession, Captain. I hear things they’re afraid to tell even their loved ones. Their fears, their sins… their pain.";
			link.l1 = "Aren’t you afraid of persecution? It’s not easy for a Catholic priest on English soil.";
			link.l1.go = "DiegoDeLanda_LadyBeth_4";
		break;

		case "DiegoDeLanda_LadyBeth_4":
			dialog.text = "My fears are nothing compared to what you just left behind that door. And that little book you took from that unfortunate woman… If fear had a form, it would be exactly like that.\n"+
		"Good day, Captain.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		//<-- Леди Бет
		
		//--> Мементо
		case "DiegoDeLanda_Memento_2":
			dialog.text = "Tiger, tiger, burning bright\n"+
			"In the forests of the night,\n"+
			"What immortal hand or eye\n"+
			"Could frame thy fearful symmetry?\n"+
			"Of course I knew him, Captain. But did you?";
			link.l1 = "I’ve never met a man with a more tragic fate.";
			link.l1.go = "DiegoDeLanda_Memento_3";
		break;

		case "DiegoDeLanda_Memento_3":
			dialog.text = "You have, but haven’t realized it yet.\n"+
			"Then you didn’t know Grim. Even as you hold his skull in your hands.";
			link.l1 = "What?!";
			link.l1.go = "DiegoDeLanda_Memento_4";
		break;

		case "DiegoDeLanda_Memento_4":
			dialog.text = "That’s no Christian way to treat the dead. Here, take this little post mortem instruction. A gift from me to you.\n"+
			"Good day, Captain.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			SetAlchemyRecipeKnown("blade_SP_3low");	// рецепты от Катласа
			SetAlchemyRecipeKnown("blade_SP_3");
		break;
		
		//<-- Мементо
		
		//--> Прощание
		case "DiegoDeLanda_Leaving":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving");
		break;
		
		case "DiegoDeLanda_Leaving_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Tell me... Why? That was dangerous and foolish. What drives you, Captain? What is your fire?";
				link.l1 = "It’s none of your business.";
				link.l1.go = "DiegoDeLanda_leaving_First_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Second.";
				link.l1 = "Last time you spoke in riddles. Will you do it again?";
				link.l1.go = "DiegoDeLanda_leaving_Second_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "...";
				link.l1 = "Wait, de Landa. I can't just let you take and leave like that.";
				link.l1.go = "DiegoDeLanda_Leaving_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
		break;
		
		case "DiegoDeLanda_Leaving_First_2": // Первое прощание
			dialog.text = "I don’t understand. The others — yes. But not you. Not yet.";
			link.l1 = "The others?";
			link.l1.go = "DiegoDeLanda_Leaving_First_3";
		break;

		case "DiegoDeLanda_Leaving_First_3":
			dialog.text = "One, for example, seeks justice. Another… obsessed with the dark waters of death. People so easily lose themselves in their desires. Don’t you think?";
			link.l1 = "You’re a strange priest, Father.";
			link.l1.go = "DiegoDeLanda_Leaving_First_4";
		break;

		case "DiegoDeLanda_Leaving_First_4":
			dialog.text = "...";
			link.l1 = "I should go.";
			link.l1.go = "DiegoDeLanda_Leaving_First_5";
		break;

		case "DiegoDeLanda_Leaving_First_5":
			dialog.text = "Of course. Your work is only beginning, Captain.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_leaving_Second_2": // Второе прощание
			dialog.text = "\nThe true riddle stands before me. You’ve already gathered two… relics. You like collecting such things? Are you a collector?";
			link.l1 = "How do you know?";
			link.l1.go = "DiegoDeLanda_leaving_Second_3";
		break;

		case "DiegoDeLanda_leaving_Second_3":
			dialog.text = "A trophy hunter?";
			link.l1 = "I repeat my question: how do you know?";
			link.l1.go = "DiegoDeLanda_leaving_Second_4";
		break;
		
		case "DiegoDeLanda_leaving_Second_4":
			dialog.text = "A thrill seeker?";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving_Second_5";
		break;

		case "DiegoDeLanda_leaving_Second_5":
			dialog.text = "\nAh. Of course. Naturally. Well then, Captain, I won’t keep you.";
			link.l1 = "Hold on, Father. You still haven’t answered my question.";
			link.l1.go = "DiegoDeLanda_leaving_Second_6";
		break;

		case "DiegoDeLanda_leaving_Second_6":
			dialog.text = "Oh, Captain. I can’t. Sometimes answers wound more than ignorance. Go in peace. And take care of your collection… of trophies. They might come in handy for the journey ahead.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_Leaving_Third_2": // Третье прощание
			dialog.text = "Come now, Captain. Isn’t it interesting to you? Aren’t you having fun? Do you have enough trophies?\n"+
			"That’s your fire, Captain. You’re curious about what comes next. You love beautiful ships and fascinating trinkets.\n"+
			"You simply can’t help but collect them all.\n"+
			"\n"+
			"You can shoot me right now.";
			link.l1 = "What?!";
			link.l1.go = "DiegoDeLanda_Leaving_Third_3";
		break;

		case "DiegoDeLanda_Leaving_Third_3":
			dialog.text = "Go ahead. But then you won’t learn everything and won’t get the complete set of trophies. Though you’ll get all the ships anyway…\n"+
			"Good day, Captain.";
			link.l1 = "(Let him go)";
			link.l1.go = "DiegoDeLanda_Leaving_End";
			link.l2 = "(Shoot him)";
			link.l2.go = "DiegoDeLanda_Leaving_Shoot";
		break;
		
		case "DiegoDeLanda_Leaving_End":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_End");
		break;
		
		case "DiegoDeLanda_Leaving_Shoot":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_Shoot");
		break;
		
		
		//<-- Прощание
	}
} 