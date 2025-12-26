// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular, "+GetSexPhrase("genç adam","genç hanımefendi")+"?","Ne istiyorsun, "+GetSexPhrase("yakışıklı","güzelim")+" Sor bakalım."),"Yine sorular","Tee-hee, eğer sizin için fark etmezse - sorular...",""+GetSexPhrase("Hm, neden kendine bir güzellik seçmiyorsun? Senden şüphelenmeye başlıyorum...","Hm, neden kendin için bir güzellik seçmiyorsun? Ne yazık ki burada hiç erkek yok, hihi...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim, affedersiniz.","Aslında, boşver."),"Ben... özür dilerim, şimdilik sorum yok.","Haklısınız, bu zaten üçüncü sefer oldu. Affedin beni.","Belki bir dahaki sefere, Madam.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Dinle Aurora, bu gece için bir kız istiyorum. Ve onu evime götürmek istiyorum. Bunu ayarlayabilir misin?";
                link.l1.go = "Gigolo";
			}	
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Gigolo":
			dialog.text = "Elbette, sevgili. Uygun bir genç kız buldun mu, yoksa ben mi ilgileneyim?";
			link.l1 = "Gerçekten de öyle yaptım. Gözüm Lucille adında bir kızda.";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "Lucille Montaigne'den mi bahsediyorsunuz?";
			link.l1 = "Doğrusunu söylemek gerekirse, soyadını sormadım. Bildiğim tek şey, adının Lucille olduğu genç, güzel, sarışın bir kız olduğu.";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "Evet, onu gerçekten çok iyi tarif ettiniz. Peki. Ama söyleyin, neden o? Diğer kızlar hoşunuza gitmedi mi?";
			link.l1 = "Bakın... buraya daha yeni başladı, bu yüzden 'meslek' konusunda henüz yeterince tecrübeli olmadığını ve cüzdanıma fazla yük olmayacağını düşünüyorum.";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "Görüyorsun, açık tenli sarışınlara bayılırım. Bu açıdan Lucille mükemmel olacak.";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "Now Monsieur, that isn't true! She is young, pretty, and experienced; my clients all but admire her. She will cost you a lot. Five thousand pesos for a night with her, and not a single peso less.";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "Pahalı, ama pekâlâ. Al paran.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Bu çok pahalı! O kadar param yok. Seninle sonra konuşurum.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "Ah, haklısınız Mösyö, genç ve güzel ama tecrübesiz. Müşterilerim genelde onu fark etmiyor, bu yüzden sordum. Ama gerçekten mütevazı kızlardan hoşlanıyorsanız, iyi bir seçim olur. Size iki bin beş yüz peso'ya mal olacak.";
				if (sti(pchar.money) >= 2500)
				{
					link.l1 = "Ne yazık ki, o işini gayet iyi yapacak. Al paranı.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Bu çok pahalı! O kadar param yok. Seninle sonra konuşurum.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "İlk sen olmazsın, yakışıklı. Zaman zaman müşterilerim onun ilgisi için sıraya girer, çünkü o, adalarımızın esmer kızlarından çok farklıdır. Onun için dört bin beş yüz peso ödemen gerekir.";
				if (sti(pchar.money) >= 4500)
				{
					link.l1 = "Pahalı, ama çok iyi. Paranı al.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Bu çok pahalı! O kadar param yok. Sonra konuşuruz.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "Gerçekten mi, Mösyö? Şimdiden memleket hasreti mi çekiyorsunuz? Benim Kreollerim ve özellikle melezlerim, bu rahat Parisli serseriden çok daha tutkuludur. Ama ne yazık ki, seçim sizin. O size üç bin peso'ya mal olacak.";
				if (sti(pchar.money) >= 3000)
				{
					link.l1 = "Pahalı, ama çok iyi. Al paranı.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Bu çok pahalı! O kadar param yok. Seninle sonra konuşurum.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "Dilediğiniz gibi, sevgili. Lucille sizi akşam saat on birde sabırsızlıkla bekliyor olacak. Ayrıca, sabah yediden geç kalmamalı. Eğer gece yarısından önce gelmezseniz, başka bir müşteriyle ilgilenecek ve onu görmek için bir sonraki akşama kadar beklemeniz gerekecek. Ve sakın... ona zarar vermeye kalkmayın, yoksa pişman olursunuz. Benden söylemesi, sevgili.";
			link.l1 = "Endişelenmeyin, ona bir zorba gibi değil, bir sevgili gibi davranacağım. Onu saat on birde alırım. Peki, o zamana kadar ne yapmalıyım?";
			link.l1.go = "Gigolo_4a";
		break;
		
		case "Gigolo_4a":
			dialog.text = "Ah, ben de bilmiyorum, canım. Meyhaneye uğra, barmenle biraz sohbet et...";
			link.l1 = "Kötü bir fikir değil. Tam da öyle yapacağım. İyi günler!";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
			QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerDelLoc("fortfrance_brothel", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
			//NewGameTip("Доступна функция перемотки времени! Она доступна через опцию 'мысли вслух' в меню действий (ENTER).");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
