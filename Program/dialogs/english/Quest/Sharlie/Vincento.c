// отец Винсенто
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
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = "At long last, I see the famed French captain "+GetFullName(pchar)+" in the flesh. I have heard much of your exploits. You are a brave soldier and, I hope, a loyal and faithful son of our Mother, the Holy Roman Catholic Church. Be seated, my son. No need to stand on my account. Dominus vobiscum! ";
				link.l1 = "Et cum spiritu tuo, Your Excellency. My journey here was long and arduous... Per aspera ad astra and all...";
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = "Yes, I can see in your eyes that you have news for me. You have my undivided attention.";
				link.l1 = "Your Excellency, I've found your missing secretary...";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = "Have you brought me news from San Jose, my son?";
				link.l1 = "Yes, Your Excellency. I have determined what happened to our mutual acquaintance Miguel Dichoso and his lost frigate. As soon as his ship entered the Atlantic en route to Spain, she was immediately caught up in a contrary gale and whirled back into the Caribbean.";
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = "Pax vobiscum, my son... What can I do for you?";
				link.l1 = TimeGreeting()+", Your Excellency. Do you have any news regarding our arrangement?"link.l1.go ="guardoftruth_17";
				break;
			}
			dialog.text = "Is there something you wanted, my son?";
			link.l1 = "No, nothing, Father.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = "'Enter by the narrow gate; for wide is the gate and broad is the way that leads to destruction, and there are many who go in by it. Because narrow is the gate and difficult is the way which leads to life, and there are few who find it.' The path of righteousness is always difficult, my son. But the aim that is achieved fully rewards a righteous man for his works.";
			link.l1 = "I agree, Your Excellency. I have completed the tasks you set before me. You already have the cowardly pirate who stole the precious vessels from the Church. Now I am returning all the items that were taken: the monstrance, the cross, and the censer. Take them for the parish of Santiago.";
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = "Benedicite! I thank you from the bottom of my heart for your faithful service to Holy Mother Church and the parish of Santiago, my son. Your works will not go unrewarded. The parishioners have collected an offering for the courageous warrior who returned their stolen items, and I gladly give it to you on their behalf. 'The labourer is worthy of his wages.'";
			link.l1 = "Thank you, Your Excellency. What a pleasant surprise!";
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			Log_Info("You've received a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Faithful service to Mother Church is always faithfully rewarded, "+pchar.name+". I, for my part, hope that you remain a dedicated warrior for the defence and protection of Christendom, for there is a deadly threat looming above us like the mythical Sword of Damocles.";
			link.l1 = "What could that be, Your Excellency?";
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = "Perhaps you are destined to be our champion in the coming battle against the dark powers and principalities of this world, my son, for there are many signs and portents that something wicked is approaching.";
			link.l1 = "Signs and portents?";
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = "Many, my son... One of them is your craving to search for the lost Indian gold of pagan Tayasal, for that which is kept in their hoard is exactly what represents danger to the whole Christian world.";
			link.l1 = "Would you be able to enlighten me a little about this gold, reverend Father? I've already heard the story of its disappearance, but what sort of threat do you speak of?";
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = "Listen closely, my son, and know that everything you are about to hear is for your ears only. Long before Miguel Dichoso took that pagan treasure out of the ancient Indian city, I had a captive man of the Itza Indians questioned regarding our mission in the Caribbean. The Itza people are descendants of the Maya, a mighty empire lost centuries before even Cristóbal Colón and his men first set foot in the New World. The Maya Empire ruled the surrounding tribes with an iron fist, wielding unspeakable power granted to them through infernal dealings with demons. Dark magics bought with the blood of generations of human sacrifices. \nThis Itza man knew about Tayasal, a lost Maya city and the incredible evil still sealed within it. He told us all he knew. If those seals are opened, the consequences would be apocalyptic. From that moment on, I have done everything I could to stop this terrible evil from being awakened. I wrote to the Escorial and Rome, desperately asking for aid.\nThey listened and dispatched Don Ramon de Mendoza y Riba, who established his base at Providence and started to search for Tayasal. That is when I discovered that the good Don Mendoza had... different motivations for finding the lost city. Rather than preventing the end of the world, he sought to serve Mammon rather than Christ.\nThat is why God abandoned him and sent the angel of death into his camp. All his actions were futile and led only to the pointless deaths of Spanish soldiers and faithful Indian converts. I wrote to the Escorial asking to discharge Ramon de Mendoza due to rank incompetence and they agreed to relieve him of his duties, but...";
			link.l1 = "Miguel Dichoso has arrived.";
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = "Kukulcan?! Sancta Maria, Mater Dei, ora pro nobis! Kukulcan again, that old serpent...";
			else sTemp = "Hm...";
			dialog.text = "Precisely. That devil-sent adventurer found Tayasal along with the treasures of the ancient Mayans. However, Don Mendosa's joy was short-lived. All those treasures disappeared along with Dichoso en route back to Spain. It's likely that, along with all the gold ingots and ornaments, Miguel took with him an ancient source of devilry, the horrifying mask of an ancient Mayan demon god named Kukulcan.";
			link.l1 = sTemp+"But what evil do you speak of, Your Excellency? How do you know about it?";
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = "It's an evil that brings death to all baptised Christians of the Caribbean, the New World, and possibly the Old World as well. The end will come like a thief in the night, and no one will even realise what happened. And there are portents of this everywhere already!";
			link.l1 = "What portents? I don't understand...";
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = "My son, are you really so blind that you don't even notice them? They've been happening for twenty-five years, almost nonstop!";
			link.l1 = "I would like to humbly mention, Your Excellency, that the span of my life is counted precisely by this length of time, not to mention I have spent most of my years in Europe. My ignorance should be somewhat excused.";
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = "I understand. "+pchar.name+". Now, haven't you noticed strange things happening across the Caribbean since you arrived here from Europe? Don't you find it strange that witchcraft, black magic, and other rituals hold far greater power here than back home? Pagan amulets enchanted by Indian shamans possess a real power that any man can feel simply by holding them.\nEven our Christian alchemists - may God make them see the error of their ways! - have mastered the art of crafting enchanted items. They do not realise that by doing so, they are serving the Devil himself. Don't you sense the unnatural presence of something infernal lurking just beyond your peripheral vision?";
			link.l1 = "You're right, Father. I was surprised by that at first, but now I suppose I've just got used to it... It's the New World, after all!";
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = "But it wasn't always like that. The darkness I am speaking of came here about twenty-five years ago and gains more and more power with each passing day. That means only one thing: 'it' has already come, 'it' is among us, and 'it' is at work...";
			link.l1 = "Who are you talking about? Who is this mysterious 'it'?";
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = "The sworn enemy of Christians, desiring the destruction of the Church and all Christendom.";
			link.l1 = "...Are you speaking of the Antichrist?";
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = "Whether it is 'the' Antichrist or just 'an' antichrist, I will not presume to say. It matters not what name this beast bears when it robes itself in mortal flesh in grotesque parody of Our Saviour's Incarnation. What is important is what it is going to do. I am here to stop it, and you are going to help me. But we've got a bit carried away. You are a man of action. You would probably prefer to get down to business and skip the theology, correct?";
			link.l1 = "On the contrary, I've learned a great deal of new and important things from you, Your Excellency. I'm ready to listen further.";
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = "You are courteous and well brought up, my son. That's good. Now, back to the reason you conferred with me. Our collective goal is to find the treasures of Tayasal taken by Dichoso. We will likely be able to find a weapon among those treasures which we can use in the coming battle against the Devil.";
			link.l1 = "But could it be that Dichoso has already left the Caribbean and is now sitting on a pile of gold back in Spain ?";
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = "No. I have proof that these treasures are still here in the Caribbean. You don't need to know about my sources yet, you have to trust me. Besides, I think that Dichoso was lying to the baron.\nHis story about the ruins of Tayasal doesn't match up with what my Itza Indian told me under questioning. Not to mention that Dichoso being the sole survivor of the Mosquito ambush was just a little bit too convenient.";
			link.l1 = "I take it that Don Mendoza believes that as well, since he raided Saint-Pierre trying to find Dichoso?";
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = "The baron's actions should not concern you, my son. He is motivated only by a lust for gold and personal gain. His greed shall be a millstone around his neck while all around him good Christian men and women are engaged with the forces of Hell.";
			link.l1 = "Do you have any leads on where we should search for Dichoso and the treasure?";
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = "I think about it every minute, my son, but I don't have anything specific to tell you. But there is a man here who will help us, a natural philosopher from Genoa. I brought him here with me to help categorise things of the New World that could be of use to the Church's mission. He witnessed the interrogation of the Itza Indian and, by my best judgement, things he had heard shocked and perversely attracted him.\nThe Devil used his curiosity like a baited wolfhook and possessed him, body and soul. The Lord had given him great ability with medicine and alchemy, but our Genoese fell into the temptation of black magic and sorcery. He spoke with my captive Itza several times without my permission, then vanished. We must find him and save his soul.";
			link.l1 = "I take it I'm supposed to find him?";
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = "Yes, my son. He is the first step to finding the treasure and the weapon that we can use against the evil forces threatening us.";
			link.l1 = "Who is this Genoese?";
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = "His name is Gino Gvineili. Thirty years of age, give or take a few. A talented physician and alchemist. As I said, he now studies black magic. According to my best intelligence, he is hiding somewhere among the English colonies in the Caribbean.\nFind Gino Gvineili, my son. If you managed to find that pirate who stole our church vessels, then you will also manage to find my runaway secretary and bring him here. I shall pray for St. Antony's intercession on your behalf.";
			link.l1 = "I see, Your Excellency. I won't waste another minute. See you later!";
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", "I almost betrayed myself by a shout of surprise. Father Vincento ordered me to find and bring him his runaway secretary, a physician alchemist named Gino Gvineili. That same Gino who occupies the spare room on the second floor of my house in St. John's!");
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", "I must find a man named Gino Gvineili, hiding somewhere in the English Caribbean colonies. He is a physician and an alchemist. Where can a man like him hide?");
			}
		break;
		
		case "guardoftruth":
			dialog.text = "I had complete faith you would say that, "+pchar.name+". Now my faith is further strengthened by my certainty that you have been sent to me by the hand of Divine Providence Itself. Where is my wretched, prodigal son?";
			link.l1 = "I'm afraid you won't like what you're about to hear, but I have no choice. Your secretary is dead.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "May God save his soul and forgive him his sins... How did it happen, my son?";
			link.l1 = "I've found Gino on Antigua. He was hiding out there in one of the old buildings constructed beneath the laboratory. He didn't agree to come along with me quietly. After hearing your name and seeing that I was prepared to use force, he took a vial of clear liquid from the folds of his long garment and drank it in an instant...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "";
			link.l1 = "And then something dreadful happened: he turned red, then dark blue. He fell to the floor, convulsing in a spasm, and within a minute died in terrible agony. A strong smell of almonds filled the room.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Gino... You poor fool... He even spent the last moments of his life in sin by committing suicide. What a tragic loss. I shall pray for his soul...";
			link.l1 = "After he died, I searched his dwelling and found this folio there. Could it possibly be of interest to you, or perhaps help us in our search? There are some strange and esoteric notes of some kind here...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info("You've given the almanac");
			PlaySound("interface\important_item.wav");
			dialog.text = "This is poor Gino's almanac. He had been writing notes in it about all his explorations. Give it to me, my child, I will study what is written here. Perhaps we will find a clue.\nThough you didn't bring Gino Gvineili back to me, I am satisfied with your efforts, my child. Now I have some news for you.";
			link.l1 = "You have my attention, Father.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "I have acquired information that the island of Trinidad was the last place where Dichoso's frigate was seen. I also know an approximate time - early April 1654.\nGo to Trinidad and try to learn anything about the frigate's fate: where she was heading, what plans the captain had, anything you can find. I understand that it has been a long time and people's memories have limits, but a drowning man will clutch at straws.";
			link.l1 = "I'll do everything in my power.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Let me see your letter of safe passage. I'll add permission for you to visit the colony of San José.";
			link.l1 = "Here.";
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = "There... that will be all. Don't forget to hoist the Spanish flag on your ship. Step forward and receive God's blessing, my son!";
			link.l1 = "One moment, Your Grace. Might I ask you a question?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Yes, of course. What would you like to know?";
			link.l1 = "During our last meeting, you spoke of an Itza Indian who had informed you about Tayasal. I've thought a lot about it... Tell me, did that man have anything on him? Objects of some kind, writings, or anything of the sort? This may prove to be useful.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "No special items, my son. A loincloth, primitive jewellery, a bamboo pipe with some herbs, and a piece of rough leather used as a gag.\nAll of those were sent to Don Ramon de Mendoza y Riba. But I assure you, there was nothing of interest.";
			link.l1 = "I see. Thank you, Father. Until next time!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = "May the Almighty bless you and keep you... What became of Miguel Dichoso? Did you find out?";
			link.l1 = "Alas, I did not. The last thing the witnesses could tell me was that the Santa Quiteria was taken by gale-force winds in the direction of Martinique. It is not known for sure whether the ship was saved or if it perished. But I have suspicions that Miguel Dichoso made it out alive.";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "What made you decide that, my son?";
			link.l1 = "The key is that the frigate was hiding somewhere in the direction of Martinique. And very recently, a gallant caballero by the name of Diego de Montoya, one of Don Ramon de Mendoza's men himself, attacked Saint-Pierre with the goal of finding Miguel Dichoso, who was supposedly hiding there.";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "So, the baron thinks Dichoso went into hiding with the French...";
			link.l1 = "I know Saint-Pierre and Governor Jacques Dyel du Parquet well, Your Excellency. Nobody knew a Spaniard named Miguel Dichoso there. Can you tell me how to find Diego de Montoya? I'd like to speak with him about Dichoso.";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Are you sure he'd be willing to speak with you, my son? I don't think he would, unless you converse with sword and pistol.";
			link.l1 = "May it be that your name might make him more amenable?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Oh, "+pchar.name+". I doubt that Don Mendoza's sworn man would be willing to come to an agreement with you. Giving him an order to arrive in San Diego for a hearing with me might be an option, but I'm not so sure Diego would be perfectly sincere with me either.";
			link.l1 = "What shall we do now, Father?";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Leave me for a little while, my son. I need to process what you've told me and also piece together all the facts that I'm already aware of from my various sources. After that I'll tell you what our next move is. Drop by later on.";
			link.l1 = "Yes, Your Grace. Will do. I'll check in periodically...";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = "God bless you, my son... What can I do for you?";
			link.l1 = "Do you have any news, Your Excellency?";
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = "Not at the moment, my son. Don't despair, though. My people and I are working on it. Drop by later.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Yes, my son. I have some information about Miguel Dichoso. It was not in vain that I believed Dichoso to still be alive and in the Caribbean. It seems Don Diego de Montoya was right. We have received confirmation from a man who recognised Miguel Dichoso by his face that the missing gentleman was seen in the pirate settlement of Le Francois on Martinique in April 1654, after the disappearance of the Santa Quiteria...";
			link.l1 = "So, the frigate foundered on the shores of Martinique?";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Slow down, my son. We don't have any information right now about any ship wrecking on Martinique at that time. And a frigate is not a lugger. Its destruction surely would have attracted some attention and created a massive salvage opportunity for local carrion feeders.";
			link.l1 = "Would it be worth searching the shoreline and beaches to find what remains of the ship?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "My son, Don Diego de Montoya, has already done all of this with no result. Keep listening. My sources at Providence report that the Baron is certain that the Santa Quiteria is still sailing across the Caribbean, though under a different name.\nThat is why he is hunting Miguel Dichoso so desperately. According to him, the Santa Quiteria was seen not far from Isla Tesoro, and she has recently been spotted under the English flag, escorted by a military squadron.";
			link.l1 = "What? This is unbelievable. They said that withstanding a storm of such scale would be impossible... And now the Santa Quiteria not only survived it but is now sailing under the English flag? The two facts don't fit. What made the Baron decide that it was the Santa Quiteria? Is she really such a unique ship?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Oh yes. This frigate was built using the latest techniques in Europe. She is very well armed for her class, and her speed allows her to outrun anything that might outgun her. That's what my source told me.";
			link.l1 = "And is she not called Santa Quiteria now?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "That, unfortunately, I do not know... Go to Isla Tesoro, "+pchar.name+", and try to find something out about Dichoso's frigate. We might manage to find her former captain that way as well, two birds with one stone. Or two rats with one trap.";
			link.l1 = "Consider it done, Your Excellency!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// проверяем, жив ли Акула и где он, если жив
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;
		
		case "tieyasal":
			dialog.text = "I'm glad you decided to see me, my son.";
			link.l1 = "Hello, Your Excellency. After meeting with Don Alonso de Maldonado, I never thought I'd see you again.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Don Alonso de Maldonado broke my direct orders. I had strictly forbidden him from confronting you, my son, I knew how it would end for him. And what I had foreseen has come true. His mission was to escort you to Tayasal, as he had been there before.\nOn top of that, his squadron and a company of Spanish soldiers were supposed to defend you against Itza or Mosquito attack. Alonso acted unworthily, driven by a selfish desire for revenge.\nHe not only failed the expedition to Tayasal and doomed the soldiers and ships entrusted to him, but also planted the seeds of distrust and resentment against me in your heart. I assure you, my son, I am completely on your side. We must stand together against this present darkness.";
			link.l1 = "I'd like to believe that.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Rest assured, "+pchar.name+". I, a loyal and devoted servant of our Lord and Saviour Jesus Christ and a representative of His Church, am driven by one purpose: to prevent the end of the world until all souls have had  a chance to hear the word of Our Blessed Lord. And that means stopping the diabolical artefact currently in the hands of a demon-possessed Indian. I suspected this from the start, and only now have I become completely certain. You have been chosen by the Lord as His champion in the battle against Satan.";
			link.l1 = "But what makes you say that, Father?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "You've managed to do something that neither I with the help of all my agents, nor Baron Mendoza and Don Diego, nor anybody else has been able to do. You've managed to find the damned island and seek out Kukulcan's artefact on it. Haven't you?";
			link.l1 = "Yes, I have Kukulcán's mask.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "And would you claim all this has happened as an accident? By coincidence? 'The heart of man plans his way, but the Lord establishes his steps.' My son, the Almighty has led you onto this path! He has fortified your hand in battle, directed your feet onto the correct path, and protected you in times of peril! 'Behold, the sword of the Lord descends for judgment upon Edom, upon the people I have devoted to destruction!'";
			link.l1 = "Ehem... Father, but the mission has basically already been accomplished. I have the mask. Doesn't that mean that Kukulcan's possessed shell cannot enter our history and change it...?";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = "You're mistaken, my son. The demon may cross through that gate whether he has this mask or not. The mask only makes it easier for him to carry out his dark deeds. The only thing that can stop him is the complete destruction of the infernal gates.";
			link.l1 = "Don Alonso told me the same thing...";
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = "And he was right! In the name of our Lord Jesus Christ and His Blessed Mother, I call upon you to take up the Cross against this evil, my son! You cannot refuse the great commission that has been set upon you. I and all Christendom are depending on you, my son.";
			link.l1 = "Your Excellency, this is too much. I really feel... rather awkward...";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Your modesty is becoming, my son, but this is no time to play the blushing virgin. Do not be fainthearted or afraid, for the Lord your God goes before you to give you victory! Enter into this battle for the sake of your loved ones, for the sake of all Christians... and if not for them then for your own sake, because if that demon emerges victorious, you will perish along with everyone else.";
			link.l1 = "I suppose you've convinced me, Father. I had hesitated about my situation regarding a crusade into Tayasal, but now I no longer have any doubts. What can you help me with?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Only two men knew how to reach Tayasal: Alonso de Maldonado and Miguel Dichoso. Don Alonso is dead. And Dichoso... They told me he was recently seen in Sharptown on Isla Tesoro. Perhaps he is still there. You must find Dichoso and persuade him to be your guide.\nThrough gold or force, you must make this man take you to Tayasal. There you will find the gates of hell, and there you will seal them.";
			link.l1 = "And what about men?";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "The last company of soldiers I had was under the command of Alonso de Maldonado. Alas, I don't have the chance to assemble another troop of Spanish soldiers. I have spent all my credit with the local garrison. You'll have to do it with the help of your own men, my son. But I will give you what help I can with anything else.";
			link.l1 = "What kind of help?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "We must take every advantage we have in this fight, both material and spiritual. I have requested Father Adrian to join me here at this chapel in five days. He will bring with him holy amulets for you. Amulets which may aid the warriors of Christ in battle. He will also provide you with all kinds of potions. As for me, accept this blade, my son.\nThis is an ancient sword of the Knights Templar, a formidable weapon of our ancestors. Still sharp, and gleaming with the Church's blessing. Only the greatest of knights have had the honour of wielding it. Take it, possess it with pride, and crush the enemies of our Faith with the name of Jesus Christ on your lips!";
			link.l1 = "Thank you! This sword is absolutely amazing. I'm speechless...";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			Log_Info("You've received the Tanath");
			PlaySound("interface\important_item.wav");
			dialog.text = "God bless you, "+GetFullName(pchar)+", in this coming battle. I embower you with the Holy Cross. Almighty God, in whose hand victory rests and who also gave David miraculous strength to crush Goliath: humbly we pray your mercy to bless these weapons by your life-giving mercy; and grant your servant "+GetFullName(pchar)+" who wills to bear them, that he may use them freely and victoriously for defending Holy Mother Church against the attacks of all enemies visible and invisible. Through Christ our Lord. Amen.";
			link.l1 = "Amen!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "And now be gone, my son. May God watch over you, may He never leave you, not in your search, not on your path, and not in battle. Seek out Miguel Dichoso and make your way to Tayasal with his aid. Do not forget about Father Adrian, he will equip you with any amulets and remedies that you may need. And now it's time for me to return to Santiago. Goodbye, my son. Vaya con Dios.";
			link.l1 = "Goodbye, Father Vincento...";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
