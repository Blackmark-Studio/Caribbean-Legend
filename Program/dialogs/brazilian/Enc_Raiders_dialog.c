void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			int iMoney = makeint(makeint(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(LinkRandPhrase("Have you heard? The local robber " + GetFullName(npchar) + " found a new victim. One captain got scared and bought off. They say, he gave him " + FindRussianMoneyString(iMoney) + ", he-he... ", 
				"Yeah, captain " + GetFullName(pchar) + ", I already heard that you had to pay " + FindRussianMoneyString(iMoney) + ", to buy off a local bandit, " + GetFullName(npchar) + ". Now that's what I call bad luck! Ha-ha-ha!", 
				"Have you heard that the local bandits attacked one captain? He was totally robbed, he lost " + FindRussianMoneyString(iMoney) + "!"), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("Have you heard? That bandit " + GetFullName(npchar) + " has finally found justice. He and his boys tried to rob "+ GetSexPhrase("some captain, but he turned out to be","some lady captain, but she turned out to be") +" a tough nut. So our dear robber shited his pants, ha-ha! That will be a lesson for him! Robbing the local farmers is one thing, but a brave captain is a different story!", 
				"Thank you, captain " + GetFullName(pchar) + ", for finally dealing with the gang of that bandit " + GetFullName(npchar) + ". Those rascals were really a pain in everyone's ass. We were scared to even send couriers to the farm for milk, they could have intercepted them and rob of all the money."), 
				"Have you heard, "+ GetSexPhrase("finally, some captain","finally, some lady captain") +" stopped that rascal " + GetFullName(npchar) + ", who was in 'charge' of the jungle, terrorizing all the local farmers. I do hope, it will stop them from their dirty deeds for long enough...", 
				"Have you heard that local bandit " + GetFullName(npchar) + " and his boys attempted to rob "+ GetSexPhrase("some captain","some lady captain") +"? Bah! Nothing of the sort! That captain turned out to be a tough nut. They say, he chased on these robbers over all the jungle like a shark chases flock of sardines. Thank God that there are still people who can stand up for us at time when the authorities do nothing, too busy with their dark deeds..."), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("Fique onde está e largue sua arma! Seu dinheiro ou sua vida!","Fique onde está, "+GetSexPhrase("viajante","moça")+"!) Não toque em sua arma e não faça movimentos bruscos!","Fique onde está, "+GetSexPhrase("viajante","moça")+"! Esta é uma estrada pedagiada. Se quiser passar, tem que pagar o pedágio."),LinkRandPhrase("Ei, "+GetSexPhrase("companheiro","moça")+"! Não tão rápido! Quero ver o quão pesada está sua bolsa.","Chegue mais perto, amigo. Quero ouvir o tilintar do ouro na sua bolsa.","Espere, "+GetSexPhrase("companheiro","moça")+". Eu e os rapazes apostamos quanto ouro caberia na sua bolsa. Agora precisamos conferir antes que as coisas fiquem violentas."),"Não tenha pressa, "+GetSexPhrase("viajante","querida")+"! Vamos ter uma conversa franca, que tal?");				
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Por que você está falando tanta besteira?","E aí?","Do que você está falando?"),"O que você quer dizer?","O que exatamente você está insinuando?");
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Bandidos?! Excelente, eu estava louco por uma briga!","Ah, vocês são bandidos! Estão se escondendo da justiça, é isso? Pois bem, parece que a justiça acabou de chegar para vocês...","Não te ensinaram que incomodar estranhos com suas bobagens é falta de educação? Parece que vou ter que te dar essa lição..."),LinkRandPhrase("Ah, você é bem insolente, não é?! Espero que sua lâmina seja tão afiada quanto sua língua.","Vejo que você domina bem as palavras, espero que também saiba manejar a espada.","Ah, bandidos! Tantos dos seus já foram enforcados, e mesmo assim vocês continuam marchando direto para a forca."),LinkRandPhrase(RandPhraseSimple("Ah, bandidos! Sabe, normalmente eu nem perco tempo falando com gente como você!","Que sujeito insolente! Fedendo como um monte de merda fumegante e ainda tem a ousadia de falar com uma pessoa decente "+GetSexPhrase("cara","garota")+"."),"Não vou perder tempo com palavras, mas minha pistola será bem mais eloquente!","Bandidos de novo! Olha, não vou te prometer a forca, mas posso muito bem te encher de buracos na barriga!"));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase("E você sabe que uma patrulha está me seguindo de perto? Eu poderia simplesmente assobiar e você estaria acabado.",RandPhraseSimple("Sabe, eu posso chamar a patrulha. Não tem medo disso? Eles estão por perto. Acho que estão procurando por você.","Uma patrulha foi enviada recentemente para te encontrar, e eles podem chegar a qualquer momento. Você está correndo um grande risco."),RandPhraseSimple("I'd advise you to run as fast as you can. A patrol is heading this way; I've just spoken with their officer.","I would gladly continue our conversation, but I'm afraid the patrol unit I just met won't let our acquaintance develop into a close friendship."));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase("Não se faça de bobo! Dinheiro na mão e talvez aí eu te deixe ir!","Você ainda não ouviu falar da taxa de passagem? Se não largar o ouro, vai largar a cabeça!","Heh, essa pequena aventura vai te custar uma bolsa... se eu não ficar bravo."),RandPhraseSimple("É muito simples. Você nos entrega todo o seu ouro e então está livre para ir embora, ou fica aqui e nós pegamos todo o seu ouro de qualquer jeito. Mas acho que essa última opção não é do seu interesse, he-he.","Não finja que não entende! Entregue sua bolsa se não quiser que eu a tire do seu cadáver!"),"Vou explicar, já que você é tão lerdo. Me dê todo o seu dinheiro, se valoriza a sua vida.");
			Link.l1 = "Maldito seja, canalha! Eu só tenho "+makeint(makeint(Pchar.money)/20)*10+" pesos.";
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Quer o meu dinheiro? Venha pegar, e vamos ver quanto você vale!","Como você ousa, grosseirão! Vou te ensinar uma lição de bons modos!","Que autoconfiança! Bem, vamos ver como você se sai contra um verdadeiro "+GetSexPhrase("lobo do mar","Loba dos Mares")+"!"),LinkRandPhrase("Você deveria ser açoitado por tamanha afronta!","Seus canalhas! Rezem aos seus demônios por um lugar quente no inferno!","Vocês já deviam ter sido enforcados há muito tempo, bando de condenados! Pois bem, parece que vou ter que manchar meu sabre com o sangue de vocês!"),RandPhraseSimple("E o que te faz pensar que eu te daria o meu dinheiro?","E você não percebeu que estou bem armado e não vim aqui só para passear?"));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 90;  
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("Droga! Tudo bem, pode ir embora. Mas nem pense em fazer barulho enquanto estiver aqui!","Dessa vez você teve sorte, mas da próxima vai nos dever o dobro! Não se esqueça de nos lembrar, heh-heh.");
				Link.l1 = RandPhraseSimple("Mas é claro.","Corre logo, enquanto ainda dá tempo.");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk = makeint(pchar.reputation.nobility) < 51 && makeint(pchar.reputation.nobility) > 41; // Captain Beltrop, 23.01.21 - жесть!!! Надо было всего лишь убрать единичку!
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("Vamos te matar em silêncio, você nem vai conseguir soltar um pio.","Maldição! Vamos ter que te matar rápido antes que você dê o alarme.");
					Link.l1 = "Bem, esse é o seu funeral. Eu te avisei.";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("E por que eu deveria me importar com a sua patrulha? Eu pago eles. Então, me dá sua bolsa e para de falar besteira.","Você acha que pode me assustar? Eu mesmo sou a patrulha para gente como você nessa selva. Ninguém saiu daqui sem pagar uma taxa!");
					Link.l1 = "Maldito seja, canalha! Eu só tenho "+makeint(makeint(Pchar.money)/20)*10+" pesos.";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase("Heh, não vou receber ordens de um frouxo como você.","Vou abrir uns buracos novos no seu crânio por tanta ousadia! Só pra ventilar um pouco esse seu cérebro.","Tanta ousadia não ficará sem punição!"),"Você não devia ter feito isso...");
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
		    bool isStrong = (GetCharacterSkillToOld(Pchar, "FencingL") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 7);
			bool z_ok = (isStrong) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation.nobility) <= 30); // Captain Beltrop & mitrokosta, 23.01.21 проверяем на оружие (новый вариант)
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Ei, não se empolgue tanto, "+GetSexPhrase("companheiro","moça")+"! Eu só estava brincando! Pode seguir seu caminho!","Certo, mudei de ideia. Pode ir, se é tão imponente assim."),"O quê, um "+GetSexPhrase("'capitão valente'","'moça militante'")+"? De novo? Tudo bem, vá em paz...","Relaxa, "+GetSexPhrase("companheiro","moça")+". Veja, nós estávamos enganados, "+GetSexPhrase(" pensamos que você fosse um comerciante "," achamos que você era um comerciante")+". Pode ir.");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("Certo, até a próxima!","Você devia parar de roubar as pessoas, enquanto ainda pode.","Certo, mas se eu te encontrar de novo..."),RandPhraseSimple("Da próxima vez, preste atenção a quem você está ameaçando, seu cão.","Graças a Deus estou de bom humor hoje."),RandPhraseSimple("Esse comércio criminoso vai acabar te matando no fim. Adeus.","É uma decisão sábia. Bem, boa sorte!"));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("Não, amigo. Agora vou te ensinar um pouco de bons modos!","Ah, ficou assustado? Bem, cada um tem que responder pelos seus atos, não é?","Não! Eu não vou me acalmar até arrancar sua pele viva!");
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase("E você poderia ter ido em paz! Agora só pode culpar a si mesmo!","Você não devia ter começado isso, seu canalha! Agora vai morrer como um cachorro!","Ah, então! Vou te despedaçar! Arrancar seu fígado e dar pros cães comerem!");
				Link.l1 = RandPhraseSimple("Vou enfiar suas palavras de volta na sua garganta!","Com quem você pensa que está mexendo, seu verme?!");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(makeint(makeint(Pchar.money)/20)*10 >= makeint(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Beleza! Entregue isso e suma daqui!","Não é muito, mas ainda é melhor do que nada. É bom lidar com alguém inteligente! Você está livre para ir."),"Agora essa já é outra história! Como meu amigo costumava dizer, 'é sempre bom ouvir alguém inteligente, mas conversar com um tolo é muito melhor'! He-he!","Em troca do seu ouro, vou te dar um conselho: você não deveria andar pela selva se você "+GetSexPhrase("que covarde. Vai beber seu rum na taverna, assim você e sua bolsa ficam em segurança!","uma moça. Ser roubada não é o pior que poderia ter acontecido com você.")+".");
				Link.l1 = "Maldito seja!";
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = "Acho que você está tentando me passar a perna! Não se preocupe, vou te fazer cócegas com minha faca, e talvez alguma coisa acabe caindo.";
				Link.l1 = "Droga!";
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("Você de novo? Corre pra casa pra sua mamãe antes que eu fique bravo com você!","O quê? Ainda não me deu todo o seu ouro? Ha-ha!","Olha, "+GetSexPhrase("companheiro","moça")+", já cansei de você! Saia da minha frente enquanto ainda está vivo!");
			Link.l1 = "Sim, já estou indo embora.";
			Link.l1.go = "Exit";
			Link.l2 = "Eu achei que não seria justo. Então decidi consertar as coisas...";
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("O que mais você quer? Já combinamos que você vai embora!","Me deixe em paz, "+GetSexPhrase("companheiro","moça")+". Eu cuido da minha vida, você da sua, e não precisamos tentar nos dar bem!","Vá embora agora, "+GetSexPhrase("companheiro","moça")+"! Droga, você está mesmo disposto a entregar todo o seu dinheiro?");
			Link.l1 = "Sim, já estou indo embora.";
			Link.l1.go = "Exit";
			Link.l2 = "Eu lembrei que você não se despediu! Então vamos nos despedir direito...";
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("Me deixe em paz! Socorro! Eu quero viver!","Me ajude! "+GetSexPhrase("Ele é um maníaco","Ela é uma maníaca")+"! Não me mate!","Me poupe! Eu sou só um humilde bandido! Sou jovem demais pra morrer!");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Se tivesse ficado em casa, ainda estaria vivo!","Você devia ter pensado nisso antes!","Você devia saber que sempre há consequências!"),"Cedo ou tarde, isso ia acontecer.","Tarde demais para se arrepender, agora lute, canalha!");
			Link.l1.go = "exit_Fight";			
		break; 				
	}
}
