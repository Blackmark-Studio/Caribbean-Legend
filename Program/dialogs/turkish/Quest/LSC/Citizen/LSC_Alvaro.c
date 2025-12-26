// Альваро Гомец - капитан
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
				dialog.text = "Beyim, size hiçbir şey söylemeyeceğim! Masum insanlara sebepsiz yere saldırıyorsunuz. Defolun buradan!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ah, yeni bir yüz! Hoş geldin! Ne zaman geldin buraya? Son zamanlarda bir gemi kazası hatırlamıyorum.";
				link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+"Ve gemim gece sessizce ve hızla battı. Mürettebatımdan yalnızca ben adaya yüzerek ulaştım...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Bir şey mi istiyorsun?";
				link.l1 = LinkRandPhrase("Bana anlatacak ilginç bir şeyin var mı?","Adada yeni bir şey oldu mu?","Bana son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu görmek istemiştim. Hoşça kal!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Anladım. Ah, kendimi tanıtmayı unuttum. Affedin beni, senyor. Benim adım Alvaro Gomez ve bir zamanlar bir brigantin kaptanıyım. Eh, şimdi o güzel gemim dış halkada, denizin dibinde yatıyor... O zamandan beri çok sular aktı. Ah, hayat böyle işte. Tanıştığımıza memnun oldum!";
			link.l1 = "Sizi tanıdığıma ben de memnun oldum, Señor Gomez.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Bana anlatacak ilginç bir şeyin var mı?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Sana ada hakkında birkaç soru sormak istiyorum.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Dinliyorum, señor.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Bir zamanlar kaptan olduğunu söyledin. Adaya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Bana adadaki hayat hakkında ne anlatabilirsin?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Bana söyle, burada yerliler birbirleriyle huzur içinde yaşar mı? Tabii ki klanlar hariç.";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Yerliler erzaklarını nereden buluyor?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorunuz yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Herkes gibi ben de fırtınalara yakalandım. Direğimi ve dümenimi kaybettim, sonra akıntı bizi sürükleyip kayalıklara attı. Gemim, dış halkaya bile ulaşamadan parçalandı. Birkaç kişi hayatta kaldı, ben de onlardan biriyim.";
			link.l1 = "Üzücü bir hikaye...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ne diyebilirim ki? Yaşamak için ihtiyacımız olan her şey var burada. Yine de bazen burası fazlasıyla sıkıcı oluyor, o hüzün... ilk yıl gerçekten çok zordu. Ama adaya alıştım. Zavallı karım Sabrina için üzülüyorum – herhalde öldüğümü sanıyordur. Umarım yeniden evlenebilmiştir ve mutludur.\nKendi durumun için üzülme, dostum, zamanla alışacaksın. Meyhaneye, dükkâna, kiliseye uğra, herkesle tanış – ama gerçekten gerekmedikçe Narvallara ya da Rivados’a gitme! Onlar çok kurnaz heriflerdir.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Oldukça huzurlu diyebilirim. Yazılı yasalarımız yok, ama birini sağlam bir sebep olmadan döverseniz ya da Tanrı korusun, cinayet işlerseniz, toplumdan dışlanırsınız. Hatta gecenin bir vakti denize atılmanız bile mümkün.\nBir zamanlar adada klansız birkaç kavgacı vardı - gerçekten kötü adamlardı. İlki ortadan kayboldu, ikincisi ise Tartarus'un hücrelerinde birkaç ay çürüdükten sonra öldü.\nTabii bu, kendinizi şiddetli bir saldırıdan koruyamayacağınız anlamına gelmiyor, ama genelde buradakiler oldukça sakin insanlardır. Abbot gösterişli biridir ama saldırgan değildir. Kassel tam bir pisliktir ama elini kirletmez. Pratt eski bir mahkûmdur ama zararsızdır.\nBurada iki eski donanma subayımız var - Lauderdale ve Solderra. İkisi de adanın yakınlarında deniz savaşı yaparken buraya düştüler. İkisi de hayatta kaldı ve hâlâ birbirine karşı kanlı planlar kurmaya devam ediyor.";
			link.l1 = "Büyüleyici...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Batıkların ambarlarından, en efecto. Eskiden tüm erzaklar San Augustine'de saklanır ve eşitçe paylaşılırdı. Sonra korsanlar geldi ve San Augustine'i ele geçirdi - şimdi ise adadan para sızdırıp, bir zamanlar bizim olan erzakları bize satıyorlar!\nKendi gizli depolarımız var, bu yüzden aç kalmıyoruz. Balık tutarız, kuş avlarız ama en iyi et dev yengeçlerden gelir. Etleri çok lezzetli ve besleyicidir - gerçi nadiren dış halkaya yaklaşırlar.\nOnları avlamak için dalmak ise fazla tehlikeli. Bir zamanlar suyun altında yengeç avlayacak kadar cesur bir adam vardı, ama şansı sonunda tükendi. O günden beri kimse yengeç eti için dalmadı.";
			link.l1 = "İlginç...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ladrón! Hırsız!","İstediğini öylece alabileceğini mi sanıyorsun?! Çek kılıcını!","Eşyalarımı nasıl çalarsın! Şimdi kılıcımla tanış!");
			link.l1 = "Merde!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ne?! Sandıklarımı mı yağmalamaya karar verdin? Bunu yanına bırakmam!";
			link.l1 = "Lanet olası kız!";
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
			dialog.text = LinkRandPhrase("Vay canına! Silahını indir, adamım!","Burada insanlar kılıçlarını çekip etrafta dolaşanlara pek iyi gözle bakmaz.","Dinle, caballero, kılıcını çekmiş halde dolaşmak güvenli değil. Onu yerine koy...");
			link.l1 = LinkRandPhrase("Pekâlâ.","Tabii.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Bu şehrin bir sakini olarak, sizden kılıcınızı indirmenizi rica ediyorum.","Bu şehrin bir sakini olarak, sizden kılıcınızı indirmenizi rica ediyorum.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Ne halin varsa gör.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dikkatli ol, dostum, elinde böyle bir silahla dolaşmak beni tedirgin ediyor...","Silahını önümde böyle sallama. Korkutuyorsun beni...");
				link.l1 = RandPhraseSimple("Anlaşıldı.","Onu kaldırıyorum.");
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
