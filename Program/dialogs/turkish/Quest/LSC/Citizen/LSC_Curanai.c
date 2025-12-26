// Куранай - индеец
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
				dialog.text = "Beyaz suratlı köpek, beyaz kardeşlerimize zarar verdi. Seninle konuşmam. Git.";
				link.l1 = "Ah...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Beyaz kardeş ne istiyor?";
				link.l1 = TimeGreeting()+". 'Beyaz kardeş' mi? Söylesene, siz Kızılderililer neden bize ya beyaz kardeş ya da soluk suratlı köpek diyorsunuz, hmm?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = ""+GetFullName(pchar)+"! "+TimeGreeting()+" ! Bir şey mi istiyorsun? ";
				link.l1 = LinkRandPhrase("Selam, Curanai. Son zamanlarda adada neler oluyor?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				if (CheckAttribute(npchar, "quest.answer_2"))
				{
					link.l3 = "Bana neler bulduğunu göster, belki bir şeyler alırım...";
					link.l3.go = "trade";
				}
				link.l5 = "Sadece nasıl olduğunu görmek istemiştim. Hoşça kal!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Burada hepimiz huzur içinde yaşıyoruz, beyaz kardeş. Beyaz kardeşe soluk yüzlü köpek demem. Tüm soluk yüzlüler köpek değil, ben birçok Kızılderiliye 'kızıl deri köpek' derim.";
			link.l1 = "Felsefeci gibi konuşuyorsun.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Seni anlamıyorum, beyaz kardeş. 'Filozof' ne demek?";
			link.l1 = "Önemli değil, kızıl derili kardeşim. Sadece düşünce tarzını beğendim. Benim adım "+GetFullName(pchar)+".   Seninki ne?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Adım Curanai. Beyaz kardeşin adını öğrenmekten memnun oldum.";
			link.l1 = "Curanai... Neyse, yine görüşürüz!";
			link.l1.go = "exit";
			link.l3 = "Sana ada hakkında birkaç soru sormak istiyorum, Curanai.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 4)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sor, beyaz kardeş. Cevaplarım.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Buraya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Adada ne yapıyorsun?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Eve dönmek ister misin?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Adada huzur içinde mi yaşıyorsunuz? Burada kavga ya da tartışma olur mu?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorular yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ben ve kabilemden yedi savaşçı, açık havada gözüken, bizim adaya pek de uzak olmayan küçük bir adaya gitmeye karar verdik. Bambudan bir sal yaptık ve yola çıktık. Ama fırtına aniden bastırdı ve bizi açık denize sürükledi. Toprağımızın ve adamızın ne kadar çabuk kaybolduğunu fark edemedik.\nGünlerce, gecelerce denizde sürüklendik. Bütün kardeşlerim susuzluktan ve açlıktan öldü. Yalnız ben kaldım - ruhlar bana acıdı ve salı bu adaya getirdi.";
			link.l1 = "Anlıyorum... hüzünlü bir hikaye.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "I fish; hit fish with harpoon. Rarely, rarely hit big crab. Then I happy; crab is tasty, very tasty. One crab enough for few days. And I also dive to bottom in one place, where no big crabs are. Pick yellow stone, blue stone, black stone, and pearl. Big and small. Then I sell them to white brother, white sister.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Eve gitmek istiyorum. Ama ev neresi? Köyümün nerede olduğunu ya da oraya nasıl gideceğimi bilmiyorum.";
			link.l1 = "Hmm, çok üzgünüm...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Narwhal and Rivados tribes fight often, one against another. There are two chieftains; one hates the other. Someday, one kill the other. I see this. Rest of us live in peace and don't hurt anyone. Sometimes white brothers drink fire water and swear... but no killing. ";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Dur, solgun suratlı köpek! Sahip olmadığını alma!","Solgun suratlı köpek, ben bakmazken mi aldı?! Hayır!","O maden benim, solgun suratlı köpek! Sana ait olmayanı almana izin vermem!");
			link.l1 = "Kahretsin!";
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
			dialog.text = LinkRandPhrase("Beyaz kardeşimin çıplak çeliğini görmek hoşuma gitmiyor. Koy yerine.","Beyaz kardeşler ve ablalar seni çelikle dolaşırken görmekten hoşlanmaz. Dur, kardeşim.","Kahramanlık yapma, beyaz kardeş. Kılıcını indir.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Tabii.","Üzgünüm...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ben burada huzur içinde yaşıyorum. Elinde kılıçla gitmek doğru değil.","Dur, beyaz kardeş. Çeliği indir, beni korkutuyor.");
				link.l1 = LinkRandPhrase("Pekala.","Ne halin varsa gör.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Beyaz kardeş, çeliği indir. Bu beni tedirgin ediyor...","Beyaz adam sadece kullanmayı düşündüğü zaman çelik tutar. Koy onu yerine...");
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
