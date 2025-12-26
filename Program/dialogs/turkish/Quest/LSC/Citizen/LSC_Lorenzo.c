// Лоренцо Сольдерра - испанский военный офицер
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

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
				dialog.text = "Senin gibi bir hayduda söyleyecek hiçbir sözüm yok. Defol.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hm, Fransız mısın? Sanırım konuşacak bir şeyimiz yok.";
				link.l1 = "İlginç, peki neden olmasın? Bu adada uluslararası düşmanlığın pek bir anlamı olduğunu sanmıyorum...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Bir şey mi istiyorsun? ";
				link.l1 = LinkRandPhrase("Bari bana en son haberleri anlatır mısın?","Adada yeni bir şey oldu mu?","Bana en yeni dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu merak ettim. Hoşça kal, Lorenzo.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "I don't think so. I am an officer and a gentleman; I don't fraternize with enemies of El Escorial - neither in Europe, nor the Caribbean, nor this island, nor anywhere else. Go your way, señor!";
			link.l1 = "Hu-h. Nasıl istersen...";
			link.l1.go = "exit";
			NextDiag.TempNode = "meeting_no";
		break;
		
		case "meeting_no":
			dialog.text = "Sanırım kendimi yeterince açık ifade ettim: Ülkemin düşmanlarıyla samimi olmam!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "meeting_no";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Dinliyorum.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorularım yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Fransız hırsız! Sana haddini bildireceğim!","Orospu çocuğu! Sırtım dönükken eşyalarımı mı alıyorsun? Seni öldürürüm!","Eşyalarımı çalmaya mı çalışıyorsun? Güzel. Biraz kılıç talimi yapmak istiyordum, lanet olası Fransız!");
			link.l1 = "Kendini beğenmiş soytarı! Silahını çek!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ne?! Sandıklarımı mı yağmalamaya çalışıyorsun? Bunu yanına bırakmam!";
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
			dialog.text = LinkRandPhrase("Fransız, silahını yerine koysan iyi edersin, yoksa kullanmak zorunda kalabilirsin...","Beni o silahla sınamak istiyorsan, cesaretin varsa dene... yoksa, onu yerine koy.","Bir kılıcın olması seni ne asil yapar ne de yakışıklı, francés. Kılıcını indir.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Fransız, silahını yerine koysan iyi edersin, yoksa sana onu kullandırmak zorunda kalabilirim...","Eğer kendini cesur hissediyorsan o silahla beni sınayabilirsin... yoksa, onu yerine koy.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Buna gerek yok... Onu kaldırıyorum.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Fransız, silahını yerine koysan iyi edersin, yoksa kullanmak zorunda kalabilirsin...","Beni o silahla sınamak istiyorsan, cesaretin varsa dene... yoksa, silahını indir.");
				link.l1 = RandPhraseSimple("Buna gerek yok, kaldırıyorum.","Bunu kaldırıyorum.");
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
