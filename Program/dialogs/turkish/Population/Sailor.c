//Jason общий диалог уличных матросов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//найм в команду
				{
					dialog.text = "İyi günler, "+GetAddress_Form(NPChar)+". Kendi geminin kaptanı olduğunu biliyorum. Sana bir teklifim var.";
					link.l1 = "Dinliyorum, "+GetAddress_FormToNPC(NPChar)+". Ne tür bir anlaşma?";
					link.l1.go = "crew";
					link.l2 = "Üzgünüm, "+GetAddress_FormToNPC(NPChar)+", ama acelem var.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Hey, kaptan! Sıradan bir denizciden ne istiyorsun?","İyi günler, efendim. Size nasıl yardımcı olabilirim?","İyi günler, efendim. Bir şeye ihtiyacınız var mı?");
				link.l1 = "Tanıştığımıza memnun oldum, dostum! Benim adım "+GetFullName(pchar)+" . Konuşacak bir dakikan var mı?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Sana bir sorum var.","Bu koloni hakkında biraz bilgiye ihtiyacım var.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Sadece merhaba demek istedim. Görüşürüz!";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Yine siz misiniz, efendim? Başka ne istiyorsunuz?";
				link.l1 = "Konuşacak bir dakikan var mı?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Sana bir sorum var.","Bu koloni hakkında biraz bilgiye ihtiyacım var.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Yok, dostum, önemli bir şey değil. İyi şanslar!";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" hizmetinizdeyim, efendim! Ne öğrenmek istersiniz?","Sizinle konuşmak güzel, Kaptan!","Pekâlâ... Sanırım konuşmak için hâlâ biraz vaktim var...","Ne yazık ki, şimdi gitmem gerekiyor. Hoşça kal!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Bana anlatacak ilginç bir şeyin var mı?","Bana anlatacak ilginç bir şeyin var mı?","Bana anlatacak ilginç bir şeyin var mı?","Tabii. Bol şans!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

		case "crew":
			switch (hrand(2))
			{
				case 0: sTemp = "Me and my messmates were put shoreside from our last ship due to various sickness and injuries. But we are all healthy now and want to get back to work as sailors again. Do you want to hire us?"; break;
				case 1: sTemp = "Me and a few of my boys were paid off from a merchantman due to the end of its contract. We have been without a single piece of eight for a long time already so we want to get back to work again. Do you need some skillful sailors for your crew?"; break;
				case 2: sTemp = "Me and my mates just got back from a voyage two weeks ago. The ship's master has dismissed us and we've been having some great fun. But our pockets are empty now so it's time to set sail again. Do you want to hire us, captain?"; break;
			}
			dialog.text = sTemp;
			link.l1 = "Pekala, teklifinizi konuşmaya hazırım. Kaç kişisiniz ve yetenekleriniz neler?";
			link.l1.go = "crew_1";
			link.l2 = "Üzgünüm denizci, ama zaten yeterince adamım var. Kendine başka bir kaptan bulmalısın.";
			link.l2.go = "exit";
		break;
		
		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "We are the best in working with sails and tackles. Not being overly modest, I'd say that we are professionals at ship handling, so don't worry, we won't let you down even in the strongest storms."; break;
				case 1: sTemp = "Most of all we like to be on the gun deck. Few of us even served on real warships. We can load and fire cannons in the way no one in your crew can. You can count on us in every hard fight!"; break;
				case 2: sTemp = "We're proper good boarders captain, did a few runs on privateers before this. We know the glitter of cutlasses and the smell of gunpowder and blood. That's our calling. It's not easy to defeat us in a hand-to-hand fight so you can always count on our blades, captain!"; break;
			}
			dialog.text = "Var "+sti(npchar.quest.crew.qty)+" aramızdayız ve sadece birlikte işe alınırız. Tüm temel denizci görevlerini yerine getirebiliriz."+sTemp+"";
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "Aradığım adamlara benziyorlar. Peki, avansınız ne olacak?";
				link.l1.go = "crew_2";
				link.l2 = "Üzgünüm denizci, ama şu anda başka yeteneklere ihtiyacım var. Kendine başka bir kaptan bulsan iyi olur.";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "Üzgünüm denizci, ama gemimde yeterince yer yok. Kendine başka bir kaptan bulmalısın.";
				link.l1.go = "exit";
			}
		break;
		
		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" her biri için. Ve sonra sıradan bir denizcinin aylık ücreti. Fazlasını istemeyiz, kaptan.";
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "İşe alındın! Al paralarını. Şimdi gemime git, adı '"+pchar.ship.name+"', tam limanın içinde. Lostromos size tayfa kamarasında hamaklarınızı gösterecek ve yemek düzeninizi ayarlayacak.";
				link.l1.go = "crew_3";
			}
			link.l2 = "Maalesef, hepinizin ücretini ödeyemem. Kendinize başka bir kaptan bulmalısınız.";
			link.l2.go = "exit";
		break;
		
		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "Başüstüne, kaptan! Adamları toplayıp hemen yola çıkacağız.";
			link.l1 = "Çabuk ol, her an yelken açabiliriz.";
			link.l1.go = "crew_4";
		break;
		
		case "crew_4":
			DialogExit();
			AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(pchar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(pchar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(pchar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(pchar, "Soldiers", iTemp); break;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(pchar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Hey, kılıcını kınına koy, kaptan. Hiçbirimiz belaya bulaşmak istemeyiz, değil mi?","Hey, kılıcını kınına koy, kaptan. Hiçbirimiz bela istemiyoruz, değil mi?");
			link.l1 = LinkRandPhrase("Pekala.","Dediğiniz gibi olsun.","Dediğiniz gibi.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
