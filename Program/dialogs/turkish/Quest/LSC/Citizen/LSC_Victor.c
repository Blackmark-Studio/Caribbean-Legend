// Виктор Кассель - бандит
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
				dialog.text = "Defol git, dostum. Masum insanları kavgaya kışkırtanlarla konuşmak istemiyorum. Kaybol!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hm... Ne istiyorsun dostum? Sohbet etmeyi umuyorsan, seni hayal kırıklığına uğratacağım...";
				link.l1 = "Ne yazık... Aslında konuşmak isterdim. Buraya yeni geldim ve insanları yeni yeni tanıyorum...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! Ne istiyorsun?";
				link.l1 = LinkRandPhrase("Victor! Bana anlatacak bir haberin var mı?","Adada yeni bir şey oldu mu?","Bana son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu merak ettim. Hoşça kal.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Yeni biri mi? Hm... Pekâlâ. Ben Victor Cassel. Beni kötü bir ruh halindeyken sinirlendirmemeye bak. Hatta iyi bir ruh halindeyken de. Sohbetle vakit kaybetmem - biri üstüme gelirse, ben de geri iterim. Hem de sertçe. ";
			link.l1 = "Ben "+GetFullName(pchar)+", ben de gerektiğinde ısrarcı olabilirim, ama umarım buna gerek kalmaz. Eğer sohbet etmek istemezsen, seni rahatsız etmem. Hoşça kal.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Victor!   Bana haberin var mı?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Sana ada hakkında birkaç soru sormak istiyorum.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Çabuk ol.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Buraya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Burada hayat nasıl görünüyor?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Burada en önemli kişi kim?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Adada nereden para kazanabilirim?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorunuz yok mu? Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Neden umursuyorsun? Bunun hakkında konuşmak istemiyorum, özellikle de tanımadığım bir adamla.";
			link.l1 = "Tanrım... üzgünüm.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Sıkıcı görünüyor. Yorucu, tekdüze, anlamsız bir sıkıcılık. Köpekbalığı'nın korsanlarına katılacağım - en azından o çocuklar arada bir kavga ediyorlar. Eminim bir gün adadan çıkmanın yolunu da bulurlar. O gün geldiğinde, onların yanında olmak istiyorum.";
			link.l1 = "Gerçekten...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Amiral kesinlikle başta! Narvalar ve Rivados onun avucunda, onlar da buna hiçbir şey yapamıyor. Ondan sonra ise klanların liderleri gelir: Narvaların Donald Greenspy'si ve Rivados'un Kara Eddy'si. Sonra Narvalı tüccar Axel Yost gelir. Ardından meyhaneci Sancho Carpentero - sağlam bir içki olmadan burada yaşanmaz, heh!";
			link.l1 = "Anladım...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Chests, of course, but you have to beat the locks, first; people don't trust each other here, so all chests have locks. And let me tell you, pal, the best trinkets are kept inside the ships under the watch of their owners.\nYou can also explore the outer ring, but take care not to fall through the rotten decks. Or you can hunt giant crabs; you can get a good price for the meat on their pincers.";
			link.l1 = "Anladım...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Hey, hergele! Sana benimle fazla samimi olma demedim mi? Ellerini göğsümden çek!","Seni zorba biri olduğunu biliyordum. Beni soymaya kalkarsan sana gününü gösteririm!","Oh iyi, sana karşı biraz baskıcı olmak için bir bahane arıyordum!");
			link.l1 = "Argh!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ne?! Sandıklarımı mı yağmalamaya karar verdin? Bunu yanına bırakmam!";
			link.l1 = "Aptal kız!";
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
			dialog.text = LinkRandPhrase("Dostum, o kılıcı yerine koy. Komik görünüyorsun.","Biliyor musun dostum, Köpekbalığı bunu kaldırmazsan seni Tartarus'a atar...","Şu kılıcı çekip durma, aptal gibi görünüyorsun.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dostum, o kılıcı indir. Komik görünüyorsun.","Biliyor musun dostum, Köpekbalığı onu yerine koymazsan seni Tartar'a fırlatır...");
				link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dostum, o kılıcı indir. Çok komik görünüyorsun.","Şu kılıcı çekip git, aptal gibi görünüyorsun.");
				link.l1 = RandPhraseSimple("Anladım.","Bunu alıyorum.");
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
